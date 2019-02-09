/**
	@file    	MOTOR.cpp
	@author  	ELECHOUSE
	@version 	V2.0
	@date    	2012-6-22
	@brief      head file for 50A-Dula Channel Motor Driver Board

    NOTE:
	  define MOTOR_V1 or MOTOR_V2 to choose hardware
	@section  HISTORY
	V2.0	2012-12-30	Hardware change, pin redefine
    V1.0	2012-06-22	Initial version.

    Copyright (c) 2012 www.elechouse.com  All right reserved.
*/
#ifndef __MOTOR_H
#define __MOTOR_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "wiring_private.h"

#ifndef __TYPE_REDEFINE
#define __TYPE_REDEFINE
typedef uint8_t u8;
typedef int8_t  s8;
// typedef uint16_t u16; // Commented to avoid conflict when compiling
typedef int16_t  s16;
typedef uint32_t u32;
typedef int32_t  s32;
#endif

//Define your motor pins below
// #define MOTOR_V1
#define MOTOR_V2

#ifdef MOTOR_V1
#define A_EN                22   //Originally 2
#define A_RPWM              9    //OC2B //Originally 3
#define A_DIS               4
#define A_LPWM              10   //OC0B //Originally 5

#define B_EN                23   //Originally 8
#define B_RPWM              11   //OC1A //Originally 9
#define B_DIS               7
#define B_LPWM              12   //OC0A //Originally 6


#define A_RPWM_ON()         sbi(TCCR2A, COM2B1);
#define A_RPWM_OFF()        cbi(TCCR2A, COM2B1);
#define A_LPWM_ON()         sbi(TCCR0A, COM0B1);
#define A_LPWM_OFF()        cbi(TCCR0A, COM0B1);

#define B_RPWM_ON()         sbi(TCCR1A, COM1A1);
#define B_RPWM_OFF()        cbi(TCCR1A, COM1A1);
#define B_LPWM_ON()         sbi(TCCR0A, COM0A1);
#define B_LPWM_OFF()        cbi(TCCR0A, COM0A1);

#define MOTOR_CLK_PRESCALER 8

//Define your motor pins below
#elif defined MOTOR_V2

#define A_EN                22    //Originally 2
#define A_RPWM              9    //OC2B //Originally 3
#define A_DIS               4
#define A_LPWM              10   //OC2A //Originally 11

#define B_EN                23    //Originally 8
#define B_RPWM              11    //OC1A //Originally 9
#define B_DIS               7
#define B_LPWM              12   //OC1B //Originally 10

#define A_RPWM_ON()         sbi(TCCR2A, COM2B1);
#define A_RPWM_OFF()        cbi(TCCR2A, COM2B1);
#define A_LPWM_ON()         sbi(TCCR2A, COM2A1);
#define A_LPWM_OFF()        cbi(TCCR2A, COM2A1);

#define B_RPWM_ON()         sbi(TCCR1A, COM1A1);
#define B_RPWM_OFF()        cbi(TCCR1A, COM1A1);
#define B_LPWM_ON()         sbi(TCCR1A, COM1B1);
#define B_LPWM_OFF()        cbi(TCCR1A, COM1B1);

#define MOTOR_CLK_PRESCALER 8
#else

#endif


typedef enum{
    A=0,
    B=1,
}motor_ch_type;
typedef enum{
    FORWARD,
    REVERSE,
}motor_direction_type;

class MOTOR_CLASS{
public:
    MOTOR_CLASS(void);
    void begin(void);
    void set(motor_ch_type ch, u8 speed, motor_direction_type dir);
    void close(motor_ch_type ch);
private:
    void close_pwm(motor_ch_type ch);
};

extern MOTOR_CLASS motor;

#ifdef MOTOR_V1
unsigned long motor_micros();
unsigned long motor_millis();
void motor_delay(unsigned long ms);
#elif defined MOTOR_V2
#define motor_micros()		micros()
#define motor_millis()		millis()
#define motor_delay(x)		delay(x)
#endif

#endif
