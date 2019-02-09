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

void setup(void){
    Serial.begin(115200);
    /** motor driver initialize */
    motor.begin();
    /**
    NOTE:
    motor.begin() will change the prescaller of the timer0,
    so the arduino function delay() millis() and micros() are
    8 times slow than it should be.
    Please use motor_delay(), motor_millis(), motor_micros() instead them.
    */

    Serial.println("motors_testing.ino");

    /** set led pin output */
    pinMode(13, OUTPUT);
}


void loop(void){
    // digitalWrite(13, HIGH);         // set the LED on
    //
    Serial.println("Moving forward @ 127");
    motor.set(A, 127, FORWARD);     // channel A FORWARD rotation
    // // motor_delay(2000);
    // // Serial.println("Moving B forward @ 127");
    motor.set(B, 127, FORWARD);     // channel B FORWARD rotation
    motor_delay(3000);              // wait for 3 seconds
    //
    // digitalWrite(13, LOW);          // set the LED off
    //
    Serial.println("Moving reverse @ 127");
    motor.set(A, 127, REVERSE);     // channel A REVERSE rotation
    // // motor_delay(2000);
    // // Serial.println("Moving B reverse @ 127");
    motor.set(B, 127, REVERSE);     // channel B REVERSE rotation
    motor_delay(3000);              // wait for 3 seconds
    //
    // digitalWrite(13, HIGH);         // set the LED on

    // Serial.println("Moving A forward @ 240");
    // motor.set(A, 240, FORWARD);     // channel A FORWARD rotation
    // // motor_delay(2000);
    // // Serial.println("Moving B forward @ 240");
    // motor.set(B, 240, FORWARD);     // channel B FORWARD rotation
    // motor_delay(3000);              // wait for 3 seconds

    // digitalWrite(13, LOW);          // set the LED off

    // Serial.println("Moving A reverse @ 240");
    // motor.set(A, 240, REVERSE);     // channel A REVERSE rotation
    // // motor_delay(2000);
    // // Serial.println("Moving B reverse @ 240");
    // motor.set(B, 240, REVERSE);     // channel B REVERSE rotation
    // motor_delay(3000);              // wait for 3 seconds

    // Serial.println("Moving differential right @ 240");
    // motor.set(A, 127, FORWARD);     // channel A REVERSE rotation
    // motor_delay(2000);
    // Serial.println("Moving B reverse @ 240");
    // motor.set(A, 0, FORWARD);
    // motor_delay(1000);
    // motor.set(B, 127, FORWARD);     // channel B REVERSE rotation
    // motor_delay(3000);              // wait for 3 seconds

    Serial.println("Moving differential left @ 240");
    motor.set(B, 127, FORWARD);     // channel A REVERSE rotation
    // motor_delay(2000);
    // motor_delay(400);
    // motor.set(B, 0, FORWARD);
    // Serial.println("Moving B reverse @ 240");
    motor.set(A, 127, REVERSE);     // channel B REVERSE rotation
    motor_delay(3000);              // wait for 3 seconds

    motor.set(A, 127, FORWARD);     // channel A REVERSE rotation
    // motor_delay(2000);
    // motor_delay(400);
    // motor.set(B, 0, FORWARD);
    // Serial.println("Moving B reverse @ 240");
    motor.set(B, 127, REVERSE);     // channel B REVERSE rotation
    motor_delay(3000);              // wait for 3 seconds

    motor.close(A);                 // close motor channel A
    motor.close(B);                 // close motor channel B
    motor_delay(500);              // wait for 500 milli second
}
