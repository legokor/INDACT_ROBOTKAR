#ifndef __INIT_H
#define __INIT_H

#define ENABLE_BOTH 0
#define DISABLE_RIGHT 1
#define DISABLE_LEFT 2
#define DISABLE_BOTH 3

#include "stm32f4xx.h"

extern TIM_HandleTypeDef htim2;
extern UART_HandleTypeDef huart1;
extern volatile int dir_enableA;
extern volatile int dir_enableB;
extern volatile int dir_enableC;


void run_motorA(int);
void run_motorB(int);
void run_motorC(int);

void stop_motorA(void);
void stop_motorB(void);
void stop_motorC(void);

void init_motorA(void);
void init_motorB(void);
void init_motorC(void);

void read_button_motorA(int*);
void read_button_motorB(int*);
void read_button_motorC(int*);

void ledON(void);
void ledOFF(void);

void SendToPC(uint8_t* send, size_t length);

#endif /* __INIT_H */
