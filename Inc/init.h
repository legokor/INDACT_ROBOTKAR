#ifndef __INIT_H
#define __INIT_H

#define ENABLE_BOTH 0
#define DISABLE_RIGHT 1
#define DISABLE_LEFT 2
#define DISABLE_BOTH 3
#define MOTOR_A_ENALBE_PIN GPIO_PIN_11
#define MOTOR_A_DIR_PIN GPIO_PIN_8
#define MOTOR_A_COM_PIN GPIO_PIN_12
#define MOTOR_A_BUTTON_RIGHT GPIO_PIN_14
#define MOTOR_A_BUTTON_LEFT GPIO_PIN_13
#define MOTOR_B_ENALBE_PIN GPIO_PIN_14
#define MOTOR_B_DIR_PIN GPIO_PIN_13
#define MOTOR_B_COM_PIN GPIO_PIN_15
#define MOTOR_B_BUTTON_RIGHT GPIO_PIN_3
#define MOTOR_B_BUTTON_LEFT GPIO_PIN_4
#define MOTOR_C_ENALBE_PIN GPIO_PIN_13
#define MOTOR_C_DIR_PIN GPIO_PIN_12
#define MOTOR_C_COM_PIN GPIO_PIN_14
#define MOTOR_C_BUTTON_RIGHT GPIO_PIN_0
#define MOTOR_C_BUTTON_LEFT GPIO_PIN_1
#define MOVE_RIGHT GPIO_PIN_SET //1
#define MOVE_LEFT GPIO_PIN_RESET //0


#include "stm32f4xx.h"
#include "motor_functions.h"


extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern UART_HandleTypeDef huart1;

void init_motorA(void);
void init_motorB(void);
void init_motorC(void);

void ledON(void);
void ledOFF(void);

void SendToPC(uint8_t* send, size_t length);

#endif /* __INIT_H */
