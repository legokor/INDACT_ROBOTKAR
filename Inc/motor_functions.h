/*
 * File name: motor_functions.h
 * This .h header file contains the motor function declarations and the used variables.
 * 
 * date: 29.03.2019
 */


#ifndef __MOTOR_FUNCTIONS_H
#define __MOTOR_FUNCTIONS_H

#include "stm32f4xx.h"
#include "init.h"


extern volatile int dir_enableA;
extern volatile int dir_enableB;
extern volatile int dir_enableC;
extern int setDirA;
extern int setDirB;
extern int setDirC;


void run_motorA(int);
void run_motorB(int);
void run_motorC(int);
void run_actuator(int);

void stop_motorA(void);
void stop_motorB(void);
void stop_motorC(void);
void stop_actuator(void);

void read_button_motorA(int*);
void read_button_motorB(int*);
void read_button_motorC(int*);
void read_button_actuator(void);

#endif /* __MOTOR_FUNCTIONS_H */
