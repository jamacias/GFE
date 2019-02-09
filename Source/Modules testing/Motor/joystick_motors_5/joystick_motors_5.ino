/**
  @file       MotorDemo
  @author     ELECHOUSE
  @version    V0.1
  @date       2012-6-22
  @brief        50A-DualChannelMotorDriverBoard demo code.
  @URL https://github.com/elechouse/motor
*/

/** import motor library */
#include <MOTOR.h>
// #include <math.h>
// #include <stdlib.h>
// #include <string.h>

// Defining joystick inputs
int x_axis = 0; //Blue
int y_axis = 1; //Green
int z_axis = 2; //Yellow

const int button1 = 7; //Brown
const int button2 = 6; //White

int x_val = 0;
int y_val = 0;
int z_val = 0;
int button1_state = 0;
int button2_state = 0;

const int centre = 1024/2;

// struct steering{
//     int left;
//     int right;
// };

void setup(void){
    Serial.begin(115200);
    pinMode(button1, INPUT);
    pinMode(button2, INPUT);
    /** motor driver initialize */
    motor.begin();
    /**
    NOTE:
    motor.begin() will change the prescaller of the timer0,
    so the arduino function delay() millis() and micros() are
    8 times slow than it should be.
    Please use motor_delay(), motor_millis(), motor_micros() instead them.
    */

    Serial.println("joystick_motors_5.ino");
}


void loop(void){
    //Read, store and correct raw values
    x_val = calculate_average(x_axis);
    Serial.print("x_val = ");
    Serial.println(x_val);
    y_val = calculate_average(y_axis);
    Serial.print("y_val = ");
    Serial.println(y_val);
    //For some reason z_axis is not working.
    // z_val = calculate_average(z_axis);
    // Serial.print("z_val = ");
    // Serial.println(z_val);
    button1_state = digitalRead(button1);
    button2_state = digitalRead(button2);

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

    // Computing the speed
    //	convert to polar
   	float r = hypot(x, y);
   	float t = atan2(y, x);

//	rotate by 45 degrees
   	t = t - 3.14159265358979323846 / 4;

//  back to cartesian
    float left = r * cos(t);
    float right = r * sin(t);

//  rescale the new coords
    left = left * sqrt(2);
    right = right * sqrt(2);

//  clamp to -245/+245 to avoid over power
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

    if(button1_state == 0 || x <= 100 && x >= -100 && y <= 100 && y >= -100){
        Serial.println("Stop!");
        motor.set(A, 0, FORWARD);
        motor.set(B, 0, FORWARD);
        motor_delay(150);
    }

    else{
        if(y >= 0){
            Serial.println("y > 0");

            //Motor A moving
            if(left < 0){
                Serial.print("Motor right moving REVERSE @ ");
                Serial.println(left_abs);
                motor.set(B, left_abs, REVERSE);
                motor_delay(75);
            }
            else{
                Serial.print("Motor right moving FORWARD @ ");
                Serial.println(left);
                motor.set(B, left, FORWARD);
                motor_delay(75);
            }

            //Moto B
            if(right < 0){
                Serial.print("Motor left moving REVERSE @ ");
                Serial.println(right_abs);
                motor.set(A, right_abs, REVERSE);
                motor_delay(75);
            }
            else{
                Serial.print("Motor left moving FORWARD @ ");
                Serial.println(right);
                motor.set(A, right, FORWARD);
                motor_delay(75);
            }
        }
        else{
            Serial.println("y < 0");
            if(x < 0 && x >= y || x > 0 && x <= -y){ //Lower third and fourth quarter
                Serial.println("x < 0 && x >= y");
                Serial.print("Motor right moving REVERSE @ ");
                Serial.print(right_abs);
                Serial.print(" and left moving REVERSE @ ");
                Serial.println(left_abs);
                motor.set(B, right_abs, REVERSE);
                motor.set(A, left_abs, REVERSE);
                motor_delay(75);
            }
            else if(x < 0 && x <= y){ //Upper third quarter
                Serial.println("x < 0 && x <= y");
                Serial.print("Motor right moving FORWARD @ ");
                Serial.print(left_abs);
                Serial.print(" and left moving REVERSE @ ");
                Serial.println(right_abs);
                motor.set(B, right_abs, FORWARD);
                motor.set(A, left_abs, REVERSE);
                motor_delay(75);
            }
            else{ //Upper fourth quarter
                Serial.println("x > 0 && x >= -y");
                Serial.print("Motor right moving REVERSE @ ");
                Serial.print(right_abs);
                Serial.print(" and left moving FORWARD @ ");
                Serial.println(left_abs);
                motor.set(B, right_abs, REVERSE);
                motor.set(A, left_abs, FORWARD);
                motor_delay(75);
            }
        }
    }

    // motor.close(A);                 // close motor channel A
    // motor.close(B);                 // close motor channel B
    // motor_delay(2000);              // wait for 500 milli second

}

int calculate_average(int axis){
    int value;
    int num = 10;
    for(int i = 0; i < num; i++){
        value += analogRead(axis);
    }
    int average = value/num;

    return average;
}
