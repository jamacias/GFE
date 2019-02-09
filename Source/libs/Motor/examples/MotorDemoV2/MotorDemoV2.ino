/**
  @file    	MotorDemo
  @author  	ELECHOUSE
  @version 	V0.1
  @date    	2012-6-22
  @brief        50A-DualChannelMotorDriverBoard demo code.
*/

/** import motor library */
#include <MOTOR.h>

void setup(void)
{
  /** motor driver initialize */
  motor.begin();
  
  /** set led pin output */  
  pinMode(13, OUTPUT);   
}


void loop(void)
{
  digitalWrite(13, HIGH);         // set the LED on
  
  motor.set(B, 127, REVERSE);     // channel B REVERSE rotation
  motor.set(A, 127, REVERSE);     // channel A FORWARD rotation
  delay(3000);                    // wait for 3 seconds
  
  digitalWrite(13, LOW);          // set the LED off
  
  motor.set(B, 127, FORWARD);     // channel B FORWARD rotation
  motor.set(A, 127, FORWARD);     // channel A FORWARD rotation
  delay(3000);                    // wait for 3 seconds
  
  digitalWrite(13, HIGH);         // set the LED on
  
  motor.set(B, 240, REVERSE);     // channel B REVERSE rotation
  motor.set(A, 240, REVERSE);     // channel A REVERSE rotation
  delay(3000);                    // wait for 3 seconds
  
  digitalWrite(13, LOW);          // set the LED off
  
  motor.set(B, 240, FORWARD);     // channel B FORWARD rotation
  motor.set(A, 240, FORWARD);     // channel A FORWARD rotation
  delay(3000);                    // wait for 3 seconds
   
  motor.close(A);                 // close motor channel A
  motor.close(B);                 // close motor channel B
  delay(500);                     // wait for 500 milli second
}
