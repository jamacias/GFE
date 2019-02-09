/*
GuimarFarmExplorerServer.ino is the main control sketch of GFE iteration 1.

Modules implemented:
 - Motors (IMS-1)
 - HC-SR04 (ultrasonic sensors)
 - HMC5883L (magnetometer - GY-273)
 - ESP8266 (WiFi connection)

Author: Javier Macias
*/

//----Importing libraries----//
#include <MOTOR.h> // Controlling motors with IMS-1 driver modules
#include <Arduino.h> // Libraries for compass HMC5883L
#include <Wire.h> // I2C library
#include <HMC5883L_Simple.h> // Compass library
#include <stdio.h> // I/O management i.e. sscanf()
#include <stdlib.h>
#include <WiFiEsp.h> // WiFi ESP8266 libraries
#include <WiFiEspUdp.h> // UDP protocol for ESP8266

// Defining WiFi parameters
char ssid[] = "ESP8266 Server";         // your network SSID (name)
char pass[] = "esp8266server";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

unsigned int localPort = 10002;  // local port to listen on

char packetBuffer[255];          // buffer to hold incoming packet

WiFiEspUDP Udp; // Create an UDP instance

// Create a compass
HMC5883L_Simple Compass;

// Defining joystick inputs
const int x_axis = 1; //Blue
const int y_axis = 2; //Green
const int z_axis = 4; //Yellow

const int button1 = 5; //Brown
const int button2 = 6; //White

// Defining HC-SR04 inputs
const int EchoPin_front_left = 30;
const int TriggerPin_front_left = 24;
const int EchoPin_front_right = 32;
const int TriggerPin_front_right = 26;
const int EchoPin_left_front = 36;
const int TriggerPin_left_front = 37;
const int EchoPin_right_front = 38;
const int TriggerPin_right_front = 39;

// Joystick-related variables
int x_val = 0;
int y_val = 0;
int z_val = 0;
int button1_state = 0;
int button2_state = 0;

const int centre = 1024/2;

const int AUTOMATIC = 0; // 1 = automatic, 0 = manual.
const int threshold = 60; // Centimeters of safe zone

float heading_command = 330;

void setup(void){
    Serial.begin(115200);
    Serial.println("GuimarFarmExplorerServer.ino");

    if(!AUTOMATIC){
        // Initializing WiFi AP
        Serial2.begin(9600);    // initialize serial for ESP module
        WiFi.init(&Serial2);    // initialize ESP module

        // check for the presence of the shield
        if (WiFi.status() == WL_NO_SHIELD) {
          Serial.println("WiFi shield not present");
          while (true); // don't continue
        }

        Serial.print("Attempting to start AP ");
        Serial.println(ssid);

        // start access point
        status = WiFi.beginAP(ssid, 10, pass, ENC_TYPE_WPA2_PSK);

        Serial.println("Access point started");
        printWifiStatus();

        Serial.println("\nStarting connection to server...");
        // if you get a connection, report back via serial:
        Udp.begin(localPort);

        Serial.print("Listening on port ");
        Serial.println(localPort);
    }

    // Defining joystick pinModes
    pinMode(button1, INPUT);
    pinMode(button2, INPUT);

    // Defining HC-SR04 pinModes
    pinMode(TriggerPin_front_left, OUTPUT);
    pinMode(EchoPin_front_left, INPUT);
    pinMode(TriggerPin_front_right, OUTPUT);
    pinMode(EchoPin_front_right, INPUT);
    pinMode(TriggerPin_left_front, OUTPUT);
    pinMode(EchoPin_left_front, INPUT);
    pinMode(TriggerPin_right_front, OUTPUT);
    pinMode(EchoPin_right_front, INPUT);

    // Initializing motors drivers
    motor.begin();
    /*
    NOTE:
    motor.begin() will change the prescaller of the timer0,
    so the arduino function delay() millis() and micros() are
    8 times slow than it should be.
    Please use motor_delay(), motor_millis(), motor_micros() instead them.
    */

    // Initializing compass
    Wire.begin();
    Compass.SetDeclination(-5, 1, 'W'); //La Laguna
    Compass.SetSamplingMode(COMPASS_SINGLE);
    Compass.SetScale(COMPASS_SCALE_130);
    Compass.SetOrientation(COMPASS_HORIZONTAL_X_NORTH);
}


void loop(void){
    //Entering manual or automatic mode
    if(!AUTOMATIC){
        // Motores parados por seguridad
        x_val = 512;
        y_val = 512;
        z_val = 512;
        button1_state = 1;
        button2_state = 1;

        // if there's data available, read a packet
        int packetSize = Udp.parsePacket();
        if (packetSize){
            Serial.print("Received packet of size ");
            Serial.println(packetSize);
            Serial.print("From ");
            IPAddress remoteIp = Udp.remoteIP();
            Serial.print(remoteIp);
            Serial.print(", port ");
            Serial.println(Udp.remotePort());

            // read the packet into packetBufffer
            int len = Udp.read(packetBuffer, 255);
            if (len > 0){
                packetBuffer[len] = 0;
            }
            Serial.println("Contents:");
            Serial.println(packetBuffer);

            // Message to decode i.e. 1023 1023 1023 1 1
            sscanf(packetBuffer,"%d %d %d %d %d %d", &x_val, &y_val, &z_val, &button1_state, &button2_state);

            Serial.print("x_val = ");
            Serial.println(x_val);
            Serial.print("y_val = ");
            Serial.println(y_val);
            Serial.print("z_val = ");
            Serial.println(z_val);
            Serial.print("button1_state = ");
            Serial.println(button1_state);
            Serial.print("button2_state = ");
            Serial.println(button2_state);

            joystick_control(x_val, y_val, z_val, button1_state, button2_state);
        }
    }
    else{ //Automatic mode
        float heading = Compass.GetHeadingDegrees();
        Serial.print("Heading: ");
        Serial.println(heading);

        int cm_front_left = calculate_distance(TriggerPin_front_left, EchoPin_front_left);
        int cm_front_right = calculate_distance(TriggerPin_front_right, EchoPin_front_right);
        int cm_left_front = calculate_distance(TriggerPin_left_front, EchoPin_left_front);
        int cm_right_front = calculate_distance(TriggerPin_right_front, EchoPin_right_front);
        Serial.print(cm_left_front);
        Serial.print("  ");
        Serial.print(cm_front_left);
        Serial.print("  ");
        Serial.print(cm_front_right);
        Serial.print("  ");
        Serial.println(cm_right_front);

        if(cm_front_left < threshold || cm_front_right < threshold){ //Try to avoid the object in front
            Serial.println("Obstacle detected!");

            if((cm_front_left < 35 || cm_front_right < 35)){ //Go reverse until it is safe to do a 90 degrees turn
                do{
                    motor.set(A, 110, REVERSE);
                    motor.set(B, 130, REVERSE);
                    motor_delay(10);
                    cm_front_left = calculate_distance(TriggerPin_front_left, EchoPin_front_left);
                    cm_front_right = calculate_distance(TriggerPin_front_right, EchoPin_front_right);
                }while(cm_front_left < 35 || cm_front_right < 35);
            }

            float obstacle_angle = calculate_obstacle_angle(cm_front_left, cm_front_right);
            Serial.print("Obstacle is @ ");
            Serial.println(obstacle_angle);

            if(cm_front_left < cm_front_right){ //Left is closer, turn right the degrees necessary to be parallel to object
                Serial.println("Turning right to avoid contact!");
                float avoid_direction = calculate_heading(heading, 90 - obstacle_angle, 0); // 0 for turning right, 1 for left
                Serial.print("Heading direction to avoid contact: ");
                Serial.println(avoid_direction);
                do{
                    motor.set(A, 130, FORWARD);
                    motor.set(B, 130, REVERSE);
                    motor_delay(10);
                    heading = Compass.GetHeadingDegrees();
                    Serial.print("Heading: ");
                    Serial.println(heading);
                    if(heading > avoid_direction && heading - avoid_direction <= obstacle_angle){
                        break;
                    }
                }while(true);

                cm_front_left = calculate_distance(TriggerPin_front_left, EchoPin_front_left);
                cm_front_right = calculate_distance(TriggerPin_front_right, EchoPin_front_right);
                cm_left_front = calculate_distance(TriggerPin_left_front, EchoPin_left_front);
                cm_right_front = calculate_distance(TriggerPin_right_front, EchoPin_right_front);

                // Go forward for awhile. Otherwise would turn again against obstacle.
                if(cm_front_left > threshold || cm_front_right > threshold){
                    do{
                        Serial.println("Going forward!");
                        motor.set(A, 110, FORWARD); //correcting drift
                        motor.set(B, 130, FORWARD);
                        motor_delay(10);
                        cm_front_left = calculate_distance(TriggerPin_front_left, EchoPin_front_left);
                        cm_front_right = calculate_distance(TriggerPin_front_right, EchoPin_front_right);
                        cm_left_front = calculate_distance(TriggerPin_left_front, EchoPin_left_front);
                        cm_right_front = calculate_distance(TriggerPin_right_front, EchoPin_right_front);

                        //Stop going forward and turn if getting closer to any object
                        if(cm_right_front < 20 || cm_front_right < threshold || cm_front_left < threshold){
                            break;
                        }
                    }while(cm_left_front < threshold);
                }
            }
            else{ //Right is closer, turn left the degrees necessary to be parallel to object
                Serial.println("Turning left to avoid contact!");
                float avoid_direction = calculate_heading(heading, 90 - obstacle_angle, 1); // 0 for turning right, 1 for left
                Serial.print("Heading direction to avoid contact: ");
                Serial.println(avoid_direction);
                do{
                    motor.set(A, 130, REVERSE);
                    motor.set(B, 130, FORWARD);
                    motor_delay(10);
                    heading = Compass.GetHeadingDegrees();
                    Serial.print("Heading: ");
                    Serial.println(heading);
                    if(heading < avoid_direction && heading - avoid_direction >= -obstacle_angle){
                        break;
                    }
                }while(true);

                cm_front_left = calculate_distance(TriggerPin_front_left, EchoPin_front_left);
                cm_front_right = calculate_distance(TriggerPin_front_right, EchoPin_front_right);
                cm_left_front = calculate_distance(TriggerPin_left_front, EchoPin_left_front);
                cm_right_front = calculate_distance(TriggerPin_right_front, EchoPin_right_front);

                // Go forward for awhile. Otherwise would turn again against obstacle.
                if(cm_front_left > threshold || cm_front_right > threshold){
                    do{
                        Serial.println("Going forward!");
                        motor.set(A, 110, FORWARD); //correcting drift
                        motor.set(B, 130, FORWARD);
                        motor_delay(10);
                        cm_front_left = calculate_distance(TriggerPin_front_left, EchoPin_front_left);
                        cm_front_right = calculate_distance(TriggerPin_front_right, EchoPin_front_right);
                        cm_left_front = calculate_distance(TriggerPin_left_front, EchoPin_left_front);
                        cm_right_front = calculate_distance(TriggerPin_right_front, EchoPin_right_front);

                        //Stop going forward and turn if getting closer to any object
                        if(cm_left_front < 20 || cm_front_right < threshold || cm_front_left < threshold){
                            break;
                        }
                    }while(cm_right_front < threshold);
                }
            }
        }
        else{
            navigate_open_space(heading, heading_command);
        }
    }
}

// Used to calculate the angle at wich the obstacle is
float calculate_obstacle_angle(float cm_front_left, float cm_front_right){
    float diff = abs(cm_front_left - cm_front_right);
    float alpha = atan2(diff, 49); //49 cm between both sensors
    float alpha_degrees = alpha * 180 / 3.14159265358979323846;
    return alpha_degrees;
}

// Used to calculate proper heading values
float calculate_heading(float heading, float obstacle_angle, int direction){
    if(direction == 0){
        if(heading + obstacle_angle > 360){
            return heading + obstacle_angle - 360;
        }
        else{
            return heading + obstacle_angle;
        }
    }
    else{
        if(heading - obstacle_angle < 0){
            return heading - obstacle_angle + 360;
        }
        else{
            return heading - obstacle_angle;
        }
    }
}

// Autonomous logic for compass when there is open space and no obstacles
void navigate_open_space(float heading, float heading_command){
    if(heading >= heading_command + 10 || heading <= heading_command - 10){ // Change direction
        if(((heading - heading_command < 0 && abs(heading - heading_command) < 180) || (heading - heading_command > 0 && abs(heading - heading_command) > 180))){
            Serial.println("Turning right to heading_command!");
            motor.set(A, 130, FORWARD);
            motor.set(B, 130, REVERSE);
            motor_delay(10);
        }
        else{
            Serial.println("Turning left to heading_command!");
            motor.set(A, 130, REVERSE);
            motor.set(B, 130, FORWARD);
            motor_delay(10);
        }
    }
    else{ // Continue forward
        Serial.println("Going forward! @ open space");
        motor.set(A, 110, FORWARD); //correcting drift
        motor.set(B, 130, FORWARD);
        motor_delay(10);
    }
}

//Calculating disctance in cm using HC-SR04 module (unfiltered)
int calculate_distance(int TriggerPin, int EchoPin){
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

void joystick_control(int x_val, int y_val, int z_val, int button1_state, int button2_state){
    x_val = 1024 - x_val;
    Serial.print("x_val = ");
    Serial.println(x_val);
    y_val = 1024 - y_val;
    Serial.print("y_val = ");
    Serial.println(y_val);

	int x = x_val - centre;
    Serial.print("x = ");
    Serial.println(x);
	int y = y_val - centre;
    Serial.print("y = ");
    Serial.println(y);

    // Computing speed and direction in function of joystick position
    // Convert to polar coordinates
   	float r = hypot(x, y);
   	float t = atan2(y, x);

    // Rotate by 45 degrees
   	t = t - 3.14159265358979323846 / 4;

    // Back to cartesian
    float left = r * cos(t);
    float right = r * sin(t);

    // Rescale the new coords
    left = left * sqrt(2);
    right = right * sqrt(2);

    // Clamp to -245/+245 to avoid over power
    left = fmax(-245, fmin(left, 245));
    right = fmax(-245, fmin(right, 245));
    Serial.print(left);
    Serial.print(" ");
    Serial.println(right);

    float left_abs = abs(left);
    float right_abs = abs(right);
    Serial.print(left_abs);
    Serial.print(" ");
    Serial.println(right_abs);

    // Controlling motors depending on joystick position
    if(button1_state == 0 || x <= 100 && x >= -100 && y <= 100 && y >= -100){ //Deadzone in centre for full stop
        Serial.println("Stop!");
        motor.set(A, 0, FORWARD);
        motor.set(B, 0, FORWARD);
        motor_delay(150);
    }

    else if(x < -100 && y <= 100 && y >= -100){ //Deadzone for stability when joystick is right
        motor.set(A, left_abs, REVERSE);
        motor.set(B, right_abs, FORWARD);
    }

    else if(x > 100 && y <= 100 && y >= -100){ //Deadzone for stability when joystick is left
        motor.set(A, left_abs, FORWARD);
        motor.set(B, right_abs, REVERSE);
    }

    else{
        if(y >= 0){
            if(x < 0 && x >= -y || x > 0 && x <= y){ //Upper second and third quarter
                motor.set(A, left_abs, FORWARD);
                motor.set(B, right_abs, FORWARD);
                motor_delay(20);
            }
            else if(x < 0 && x < -y){ //Lower second quarter
                motor.set(A, left_abs, REVERSE);
                motor.set(B, right_abs, FORWARD);
                motor_delay(20);
            }
            else{ //Lower first quarter
                motor.set(A, left_abs, FORWARD);
                motor.set(B, right_abs, REVERSE);
                motor_delay(20);
            }
        }
        else{
            // Serial.println("y < 0");
            if(x < 0 && x >= y || x > 0 && x <= -y){ //Lower third and fourth quarter
                motor.set(A, right_abs, REVERSE);
                motor.set(B, left_abs, REVERSE);
                motor_delay(20);
            }
            else if(x < 0 && x <= y){ //Upper third quarter
                motor.set(A, right_abs, FORWARD);
                motor.set(B, left_abs, REVERSE);
                motor_delay(20);
            }
            else{ //Upper fourth quarter
                motor.set(A, right_abs, REVERSE);
                motor.set(B, left_abs, FORWARD);
                motor_delay(20);
            }
        }
    }
}

// Used to calculate the average of signals received from sensors
int calculate_average(int axis){
    int value;
    int num = 10;
    for(int i = 0; i < num; i++){
        value += analogRead(axis);
    }
    int average = value / 10;

    return average;
}

void printWifiStatus(){
    // print your WiFi shield's IP address
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);

    // print where to go in the browser
    Serial.println();
    Serial.print("SSID: ");
    Serial.print(ssid);
    Serial.print("\nIP: ");
    Serial.print(ip);
    Serial.println();
}
