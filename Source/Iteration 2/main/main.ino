/*
main.ino is the main control sketch of GFE iteration 2.

An enable has been configured to wait for RPi to be fully booted. Using the
alias it is possible to enable/disable and change the control mode via SSH.
The manual mode is programmed to be controlled locally. Make sure to connect the
joystick to the DA-15 connector. Otherwise, expect noise and weird movements.
The automatic mode is based on the bubble rebound obstacle avoidance algorithm
for mobile robots article, published by IOAN SUSNEA, VIOREL MINZU and
GRIGORE VASILIU.

Modules implemented:
 - Motors (IMS-1 modules)
 - HC-SR04 (ultrasonic sensors)
 - HMC5883L (magnetometer - GY-273)
 - GY-GPS6MV2 (GPS module)
 - RPi control pins

Author: Javier Macias
*/

//----Importing libraries----//
#include <MOTOR.h> // Controlling motors with IMS-1 driver modules
#include <Arduino.h> // Libraries for compass HMC5883L
#include <Wire.h> // I2C library
#include <HMC5883L_Simple.h> // Compass library
#include <TinyGPS.h> // GPS library

// Create a compass
HMC5883L_Simple Compass;

// Only need to define two ultrasonic sensor pins.
const int EchoPin_0 = 24;
const int TriggerPin_0 = 25;

//----Robot parameters----//
const int L = 0.375; // Axle length (meters)


const int threshold = 60; // Centimeters of safe zone
const float heading_threshold = 5; // Degrees of tolerance
unsigned long lastTime = 0; // Used to store execution time of loop

// Variables related to GPS
float latitude, longitude;
unsigned long fix_age;
float latitude_command = 0;
float longitude_command = 0;
// Goal heading
// int heading_command = 110;
int heading_command = 170;

// Create a GPS
TinyGPS gps;

// Defining high-level control pins
const int enable_pin = 48;
const int mode_pin = 49;
bool enable = false; // Enable = 1; Disable = 0 if RPi is not ready
bool mode = false; // Manual = 0 (default); Automatic = 1

// Defining joystick inputs
int x_axis = 0; //Blue
int y_axis = 1; //Green
int z_axis = 2; //Yellow

const int button1 = 7; //White
const int button2 = 6; //Brown

int x_val = 0;
int y_val = 0;
int z_val = 0;
int button1_state = 0;
int button2_state = 0;

const int centre = 1024/2;

const int motors_wait = 10; //Wait for motors to move

// List of waypoints to follow
float waypoints[3][2] = {{1.111111, -1.111111}, {2.222222, -2.22222}, {3.333333, -3.333333}};

// Declaring controller variables
float lastEps = 0;
int lastCommand = 0;
float lastHeading = 0;

void setup(){
    Serial.begin(115200);
    //Initialize GPS communication
    Serial1.begin(9600);
    Serial.println("main.ino");

    // Initializing motor drivers
    motor.begin();
    /**
    NOTE:
    motor.begin() will change the prescaller of the timer0,
    so the arduino function delay() millis() and micros() are
    8 times slow than it should be.
    Please use motor_delay(), motor_millis(), motor_micros() instead them.
    */

    // Configuring HC-SR04 pins
    for(int i = 0; i < 8; i++){
        // Iterate through every sensor. Every two, next sensor EchoPin and TriggerPin.
        pinMode(EchoPin_0 + (2 * i), INPUT);
        pinMode(TriggerPin_0 + (2 * i), OUTPUT);
        delay(1); // Stabilization
    }

    // Initializing compass
    Wire.begin();
    Compass.SetDeclination(-4, 56, 'W'); // La Laguna
    Compass.SetSamplingMode(COMPASS_SINGLE);
    Compass.SetScale(COMPASS_SCALE_130);
    Compass.SetOrientation(COMPASS_HORIZONTAL_Y_NORTH);

    // Configuring joystick buttons
    pinMode(button1, INPUT);
    pinMode(button2, INPUT);

    // Configuring high-level control pins
    pinMode(enable_pin, INPUT);
    pinMode(mode_pin, INPUT);

    // Wait until RPi is ready
    do{
        enable = digitalRead(enable_pin);
        Serial.println("Waiting for RPi to be ready...");
        motor_delay(1000); // Wait for one second
    }while(!enable);
}

void loop(){
    // Wait for robot to be enabled
    enable = digitalRead(enable_pin);
    while(!enable){
        enable = digitalRead(enable_pin);
        Serial.println("Robot is disabled...");
        motor_delay(1000); // Wait for one second
    }

    mode = digitalRead(mode_pin);
    // Enter manual mode if mode is false and robot is enabled
    while(!mode && enable){
        joystick_control();
        mode = digitalRead(mode_pin);
        enable = digitalRead(enable_pin);
    }

    // Otherwise, automatic mode
    if(mode && enable){
        do{
            get_location(gps);
            Serial.print("latitude = ");
            Serial.print((float)latitude, 6);
            Serial.print(" ");
            Serial.print("latitude = ");
            Serial.println((float)longitude, 6);
            delay(500);
        }while(latitude == 0 && longitude == 0);

        for(int i = 0; i < 3; i++){
            // Set the next waypoint
            latitude_command = waypoints[i][0];
            Serial.print("latitude_command = ");
            Serial.print((float)latitude_command, 6);
            longitude_command = waypoints[i][1];
            Serial.print(" longitude_command = ");
            Serial.println((float)longitude_command, 6);

            do{
                // Recalculate heading after each iteration
                heading_command = gps.course_to(latitude, longitude, latitude_command, longitude_command);
                Serial.print("heading_command = ");
                Serial.println(heading_command);
                automatic_mode(); //Navigate
                get_location(gps);
                Serial.print("latitude = ");
                Serial.print((float)latitude, 6);
                Serial.print(" ");
                Serial.print("latitude = ");
                Serial.println((float)longitude, 6);

                enable = digitalRead(enable_pin);
            }while(!goal_is_reached(latitude, longitude, latitude_command, longitude_command) && enable);

            // Get out if !enable
            if(!enable){
                break;
            }
        }
    }
}

// Read current position
static void get_location(TinyGPS &gps){
    while (Serial1.available()){
        int c = Serial1.read();
        if (gps.encode(c)){
            // Retrieves +/- lat/long in 100000ths of a degree
            gps.f_get_position(&latitude, &longitude, &fix_age);
        }
    }
}

// Check if current location is close enough to the objective
int goal_is_reached(float latitude, float longitude, float latitude_command, float longitude_command){
    if(abs(latitude - latitude_command) <= 0.00001 && abs(longitude - longitude_command) <= 0.00001){
        return 1;
    }
    else{
        return 0;
    }
}

// Automatic mode function
void automatic_mode(){
    // Calculate current and elapsed time for PI controller
    unsigned long now = millis();
    double timeChange = (double)(now - lastTime)/1000; //Seconds
    Serial.print("timeChange = ");
    Serial.println(timeChange);

    float heading = Compass.GetHeadingDegrees();
    Serial.print("heading = ");
    Serial.println(heading);

    unsigned int *sonar_readings;
    sonar_readings = average_read_sensors();
    for(int i = 0; i < 8; i++){
        Serial.print(sonar_readings[i]);
        Serial. print(" ");
    }

    // Obstacle avoidance algorithm
    if(check_for_obstacles(sonar_readings, 0, 8)){
        Serial.println("Obstacle detected!");

        float alpha_r = 0;
        do{
            Serial.println("Computing rebound angle...");
            alpha_r = rebound_angle(sonar_readings);
            Serial.print("alpha_r = ");
            Serial.println(alpha_r);

            Serial.println("Adjusting heading.");

            heading = Compass.GetHeadingDegrees();
            Serial.print("heading = ");
            Serial.println(heading);

            if(alpha_r < 0){
                Serial.println("alpha_r < 0. Turning left.");
                // Turn left. Equivalent to compute new heading + adjust motion in the paper.
                adjust_heading(heading, alpha_r, 1, timeChange);
            }
            else{
                Serial.println("alpha_r > 0. Turning right.");
                adjust_heading(heading, alpha_r, 0, timeChange);
            }

            recheck_obstacles:
            sonar_readings = average_read_sensors();
            for(int i = 0; i < 8; i++){
                Serial.print(sonar_readings[i]);
                Serial.print(" ");
            }
            enable = digitalRead(enable_pin);
        }while(check_for_obstacles(sonar_readings, 0, 8) && enable);

        if(!goal_visible(sonar_readings) && enable){
            Serial.println("Goal is not visible. Move forward!");
            move_forward();
            goto recheck_obstacles;
        }
    }
    else{
        // No obstacles, orientate to heading.
        if(heading >= heading_command + heading_threshold || heading <= heading_command - heading_threshold){
            do{
                if(((heading - heading_command < 0 && abs(heading - heading_command) < 180) || (heading - heading_command > 0 && abs(heading - heading_command) > 180))){
                    Serial.println("No obstacles around, turning right to heading_command!");
                    rotate_right(heading_command, timeChange);
                }
                else{
                    Serial.println("No obstacles around, turning left to heading_command!");
                    rotate_left(heading_command, timeChange);
                }
                heading = Compass.GetHeadingDegrees();
                Serial.print("heading = ");
                Serial.println(heading);
                enable = digitalRead(enable_pin);
            }while ((heading >= heading_command + heading_threshold || heading <= heading_command - heading_threshold) && enable);
        }
        else{ // Continue forward
            move_forward();
        }
    }

    lastTime = now;
}

// Rotate robot to the new heading
int adjust_heading(float heading, float alpha_r, int direction, double timeChange){
    if(direction == 1){
        // Calculate the new heading. Note: 0 for turning right, 1 for left
        float avoid_direction = calculate_heading(heading, abs(alpha_r), 1);
        Serial.print("avoid_direction = ");
        Serial.println(avoid_direction);
        do{
            rotate_left(avoid_direction, timeChange);
            heading = Compass.GetHeadingDegrees();
            Serial.print("Heading: ");
            Serial.println(heading);
            enable = digitalRead(enable_pin);
        }while((heading >= avoid_direction + heading_threshold || heading <= avoid_direction - heading_threshold) && enable);
    }
    else{
        // Calculate the new heading. Note: 0 for turning right, 1 for left
        float avoid_direction = calculate_heading(heading, abs(alpha_r), 0);
        Serial.print("avoid_direction = ");
        Serial.println(avoid_direction);
        do{
            rotate_right(avoid_direction, timeChange);
            heading = Compass.GetHeadingDegrees();
            Serial.print("Heading: ");
            Serial.println(heading);
            enable = digitalRead(enable_pin);
        }while((heading >= avoid_direction + heading_threshold || heading <= avoid_direction - heading_threshold) && enable);
    }
}

// Check if goal is visible.
int goal_visible(unsigned int *sonar_readings){
    float heading = Compass.GetHeadingDegrees();

    float right_limit = calculate_heading(heading, 90, 0);
    float left_limit = calculate_heading(heading, 90, 1);

    // The goal is on the right side.
    if(heading_command > heading  && heading_command < right_limit){
        Serial.println("Checking obstacles on the right");
        if(search_goal(sonar_readings, 0, 4)){
            Serial.println("Goal was found on the right");
            return 0;
        }
        else{
            return 1; // Raise error if goal is not visible
        }
    }
    else{ // The goal is on the left side.
        Serial.println("Checking obstacles on the left");
        if(search_goal(sonar_readings, 4, 8)){
            Serial.println("Goal was found on the left");
            return 0;
        }
        else{
            return 1; // Raise error if goal is not visible
        }
    }
}

// See if goal is visible from the given sensors
int search_goal(unsigned int *sonar_readings, const int start, const int end){
    unsigned int goal_boundary[8] = {50, 50, 50, 60, 60, 50, 50, 50}; // Centimeters

    for(int i = start; i < end; i++){
        if(sonar_readings[i] <= goal_boundary[i]){
            return 1; // Raise error if goal is not found
        }
    }
    return 0;
}

// Filter sensor readings by doing the average
unsigned int *average_read_sensors(){
    unsigned int sum[8] = {0}; //Initialize to zero.
    static unsigned int average[8] = {0}; //Initialize to zero.
    unsigned int *sonar_readings;

    for(int j = 0; j < 2; j++){
        sonar_readings = read_sensors();
        for(int i = 0; i < 8; i++){
            sum[i] += sonar_readings[i];
        }
    }

    for(int k = 0; k < 8; k++){
        average[k] = sum[k]/2;
    }

    return average;
}

// Store ultrasonic sensor readings. Sequence: 0 3 6 1 4 7 2 5
unsigned int *read_sensors(){
    static unsigned int sonar_readings[8] = {0}; //Initialize to zero.
    int i = 0;
    int cont = 0;
    while(cont < 8){
        sonar_readings[i] = calculate_distance(TriggerPin_0 + (2 * i), EchoPin_0 + (2 * i));
        if(cont == 2){
            i = 1;
        }
        else if(cont == 5){
            i = 2;
        }
        else{
            i += 3;
        }
        cont++;
        delay(10); // 10 ms delay to avoid false positives
    }
    return sonar_readings;
}

// Compute rebound angle
float rebound_angle(unsigned int *sonar_readings){
    const float alpha_0 = 180/8;
    float num = 0;
    float den = 0;
    for(int i = -4; i < 5; i++){
        if(i == 0){ // Zero is not taken.
            i = 1;
        }

        float alpha_i = i * alpha_0;

        num += alpha_i * sonar_readings[i];
        den += sonar_readings[i];
    }

    float alpha_r = num/den;

    return alpha_r;
}

// Compare whether any reading is below threshold
int check_for_obstacles(unsigned int *sonar_readings, const int start, const int end){
    unsigned int bubble_boundary[8] = {20, 20, 30, 40, 40, 30, 20, 20}; // Centimeters

    for(int i = start; i < end; i++){
        if(sonar_readings[i] <= bubble_boundary[i]){
            return 1;
        }
    }
    return 0;
}

// Read the distance of an ultrasonic sensor. Raw output, unfiltered.
int calculate_distance(const int TriggerPin, const int EchoPin){
    long duration, distanceCm;

    digitalWrite(TriggerPin, LOW);  //Setting to LOW for 4us for cleaner reading
    delayMicroseconds(4);
    digitalWrite(TriggerPin, HIGH);  //Triggering for 10us
    delayMicroseconds(10);
    digitalWrite(TriggerPin, LOW);

    duration = pulseIn(EchoPin, HIGH);  //Measuring the time between pulses in microseconds

    distanceCm = duration * 10 / 292 / 2;   //Converting to cm

    return distanceCm;
}

// Used to calculate proper heading values
float calculate_heading(float heading, float alpha_r, int direction){
    if(direction == 0){
        if(heading + alpha_r > 360){
            return heading + alpha_r - 360;
        }
        else{
            return heading + alpha_r;
        }
    }
    else{
        if(heading - alpha_r < 0){
            return heading - alpha_r + 360;
        }
        else{
            return heading - alpha_r;
        }
    }
}

// PI controller for rotation of the robot
int calculate_command(float goal, double timeChange){
    float heading = Compass.GetHeadingDegrees();
    float eps = abs(heading - goal);
    float deltaPV = abs(heading - lastHeading);

    // Kp and Ti manually adjusted
    int Kp = 4;
    int Ti = 2;
    float max_command = 130;

    float command = (Kp * (deltaPV + 1/Ti * (eps * timeChange)) + lastCommand) * (max_command/180);

    // Clamp to avoid values over max_command due to excessive error/gain
    command = constrain(command, 60, max_command);

    lastEps = eps;
    lastCommand = command;
    lastHeading = heading;

    return command;
}

// Rotate left
void rotate_left(float goal, double timeChange){
    Serial.println("Rotating left!");
    float command = calculate_command(goal, timeChange);
    motor.set(A, command, REVERSE);
    motor.set(B, command, FORWARD);
    motor_delay(10);
}

// Rotate right
void rotate_right(float goal, double timeChange){
    Serial.println("Rotating right!");
    float command = calculate_command(goal, timeChange);
    motor.set(A, command, FORWARD);
    motor.set(B, command, REVERSE);
    motor_delay(10);
}

// Move forward
void move_forward(){
    Serial.println("Going forward! @ open space");
    motor.set(A, 120, FORWARD); // Drift correction
    motor.set(B, 130, FORWARD);
    motor_delay(10);
}

void joystick_control(){
    //Read, store and correct raw values from joystick
    x_val = calculate_average(x_axis);
    Serial.print("x_val = ");
    Serial.println(x_val);
    y_val = calculate_average(y_axis);
    Serial.print("y_val = ");
    Serial.println(y_val);
    // For some reason z_axis is not working.
    // z_val = calculate_average(z_axis);
    // Serial.print("z_val = ");
    // Serial.println(z_val);
    button1_state = digitalRead(button1);
    button2_state = digitalRead(button2);

    x_val = 1024 - x_val;
    y_val = 1024 - y_val;

	int x = x_val - centre;
	int y = y_val - centre;

    // Computing speed and direction in function of joystick position
    //	Convert to polar coordinates
   	float r = hypot(x, y);
   	float t = atan2(y, x);

    //	Rotate by 45 degrees
   	t = t - 3.14159265358979323846 / 4;

    //  Back to cartesian
    float left = r * cos(t);
    float right = r * sin(t);

    //  Rescale the new coords
    left = left * sqrt(2);
    right = right * sqrt(2);

    //  Clamp to -245/+245 to avoid over power
    left = fmax(-245, fmin(left, 245));
    right = fmax(-245, fmin(right, 245));

    float left_abs = abs(left);
    float right_abs = abs(right);

    // Controlling the motors
    if(button2_state == 0 || (x <= 100 && x >= -100 && y <= 100 && y >= -100)){
        Serial.println("Stop!");
        motor.set(A, 0, FORWARD);
        motor.set(B, 0, FORWARD);
        motor_delay(motors_wait);
    }
    else{
        if(y > 0){
            if(left > 0 && right > 0){
                motor.set(A, left, FORWARD);
                motor.set(B, right, FORWARD);
                motor_delay(motors_wait);
            }
            else if(left > 0 && right < 0){
                motor.set(A, left, FORWARD);
                motor.set(B, right_abs, REVERSE);
                motor_delay(motors_wait);
            }
            else if(left < 0 && right > 0){
                motor.set(A, left_abs, REVERSE);
                motor.set(B, right, FORWARD);
                motor_delay(motors_wait);
            }
        }
        else{
            if(left < 0 && right < 0){
                motor.set(A, right_abs, REVERSE);
                motor.set(B, left_abs, REVERSE);
                motor_delay(motors_wait);
            }
            else if(left > 0 && right < 0){
                motor.set(A, right_abs, REVERSE);
                motor.set(B, left, FORWARD);
                motor_delay(motors_wait);
            }
            else{
                motor.set(A, right, FORWARD);
                motor.set(B, left_abs, REVERSE);
                motor_delay(motors_wait);
            }
        }
    }
}

// Calculate average of analog values
int calculate_average(int axis){
    int value = 0;
    int num = 10;
    for(int i = 0; i < num; i++){
        value += analogRead(axis);
    }
    int average = value/num;

    return average;
}
