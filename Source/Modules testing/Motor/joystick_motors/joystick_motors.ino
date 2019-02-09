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
int x_axis = 1; //Blue
int y_axis = 2; //Green
int z_axis = 4; //Yellow

const int button1 = 5; //Marrón
const int button2 = 6; //Blanco

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

    Serial.println("joystick_motors.ino");
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

	float left;
	float right;
	float max = 0;

    // Computing the speed
	int A_speed = (0.95*(y/2 + x/2));
    Serial.print("A_speed = ");
    Serial.println(A_speed);
    Serial.print("abs(A_speed) = ");
    Serial.println(abs(A_speed));
	int B_speed = (0.95*(y/2 - x/2));
    Serial.print("B_speed = ");
    Serial.println(B_speed);
    Serial.print("abs(B_speed) = ");
    Serial.println(abs(B_speed));

    // Delimiting output up to -255 and 255
    if(abs(A_speed) >= abs(B_speed)){
        Serial.print("abs(A_speed) >= abs(B_speed), max = ");
		max = A_speed;
        Serial.println(max);
	}
	else{
        Serial.print("abs(A_speed) < abs(B_speed), max = ");
		max = B_speed;
        Serial.println(max);
	}

    // If centered, don't move motors
    if(A_speed == 0 && B_speed == 0){
        Serial.println("A_speed == 0 && B_speed == 0");
		left = 0;
		right = 0;
	}
	else{
        Serial.print("Printing unfiltered motor speeds: ");
        left = 0.95*(255/max)*A_speed;
		right = 0.95*(255/max)*B_speed;
    }

    Serial.print(left);
    Serial.print(" ");
    Serial.println(right);

    float left_abs = abs(left);
    float right_abs = abs(right);
    Serial.print(left_abs);
    Serial.print(" ");
    Serial.println(right_abs);

    // String left_state = FORWARD;
    // String right_state = FORWARD;
    if(button1_state == 0){
        Serial.println("Stop!");
        motor.set(A, 0, FORWARD);
        motor.set(B, 0, FORWARD);
        motor_delay(150);
    }

    else{
        if(A_speed < 0){
            Serial.print("Motor left moving REVERSE @ ");
            Serial.println(left_abs);
            motor.set(A, left_abs, REVERSE);
            motor_delay(150);
            // String left_state = REVERSE;
        }
        else{
            Serial.print("Motor left moving FORWARD @ ");
            Serial.println(left);
            motor.set(A, left, FORWARD);
            motor_delay(150);
        }

        if(B_speed < 0){
            Serial.print("Motor right moving REVERSE @ ");
            Serial.println(right_abs);
            motor.set(B, right_abs, REVERSE);
            motor_delay(75);
            // String right_state = REVERSE;
        }
        else{
            Serial.print("Motor right moving FORWARD @ ");
            Serial.println(right);
            motor.set(B, right, FORWARD);
            motor_delay(75);
        }
    }


    // motor.close(A);                 // close motor channel A
    // motor.close(B);                 // close motor channel B
    motor_delay(2000);              // wait for 500 milli second

}

int calculate_average(int axis){
    int value;
    for(int i = 0; i < 5; i++){
        value += analogRead(axis);
    }
    int average = value / 5;

    return average;
}
