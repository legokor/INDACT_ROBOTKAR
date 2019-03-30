/*
 * File name: motor_functions.c
 * This .c source file contains the motor functions.
 * 
 * date: 29.03.2019
 */
 
 
#include "motor_functions.h"
#include "init.h"


volatile int dir_enableA = ENABLE_BOTH;
volatile int dir_enableB = ENABLE_BOTH;
volatile int dir_enableC = ENABLE_BOTH;

int setDirA = 0;
int setDirB = 0;
int setDirC = 0;


/* Init motorA with the given DIRection
 * and runs the motor. If DIR is already set, 
 * then just run */
void run_motorA(int DIR){
	if(!setDirA)
	{
		HAL_GPIO_WritePin(GPIOC, MOTOR_A_ENALBE_PIN, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, MOTOR_A_COM_PIN, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, MOTOR_A_DIR_PIN, DIR);
		htim2.Init.Period = 10000;
		HAL_TIM_PWM_Init(&htim2); 
		setDirA = 1;
	}
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
}

/* Init motorB with the given DIRection
 * and runs the motor. If DIR is already set, 
 * then just run  -  SIDEWAYS*/
void run_motorB(int DIR){
	if(!setDirB)
	{
		HAL_GPIO_WritePin(GPIOC, MOTOR_B_ENALBE_PIN, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, MOTOR_B_COM_PIN, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, MOTOR_B_DIR_PIN, DIR);
		htim2.Init.Period = 3000;
		HAL_TIM_PWM_Init(&htim2); 
		setDirB = 1;
	}
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
}
	
/* Init motorC with the given DIRection
 * and runs the motor. If DIR is already set, 
 * then just run */
void run_motorC(int DIR){
	if(!setDirC)
	{
		HAL_GPIO_WritePin(GPIOF, MOTOR_C_DIR_PIN, DIR);
		HAL_GPIO_WritePin(GPIOF, MOTOR_C_ENALBE_PIN, GPIO_PIN_RESET); // enable
		HAL_GPIO_WritePin(GPIOF, MOTOR_C_COM_PIN, GPIO_PIN_RESET);
		htim2.Init.Period = 3000;
		HAL_TIM_PWM_Init(&htim2); 
		setDirC = 1;
	}
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
}

/* Run dc actuator */ 
void run_actuator(int DIR)
{
	if(DIR)
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, GPIO_PIN_SET);		// H-bridge control signals
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, GPIO_PIN_RESET);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, GPIO_PIN_RESET);	// H-bridge control signals
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, GPIO_PIN_SET);
	}	
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
}

/* Stop motorA and reset the DIRection */
void stop_motorA(){
	HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_2);
	setDirA = 0;
}

/* Stop motorB and reset the DIRection */
void stop_motorB(){
	HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_3);
	setDirB = 0;
}

/* Stop motorC and reset the DIRection */
void stop_motorC(){
	HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_4);
	setDirC = 0;
}

/* Stop DC actuator */ 
void stop_actuator(void)
{
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, GPIO_PIN_RESET);	//OPEN H-BRIDGE -> no current
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, GPIO_PIN_RESET);
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
}


/* Read buttons and run the motor if;
 *			- button is pressed & motor is not running(semaphore) & the desired direction IS enabled 
 * stop motor if;
 * 			- any of the previous is FALSE */
void read_button_motorA(int* semaphoreA){
	if(HAL_GPIO_ReadPin(GPIOA, MOTOR_A_BUTTON_RIGHT) && (*semaphoreA == 1) && (dir_enableA != DISABLE_BOTH) && (dir_enableA != DISABLE_RIGHT))
	{
		run_motorA(MOVE_RIGHT);
		*semaphoreA = 0;
	}
	if(HAL_GPIO_ReadPin(GPIOA, MOTOR_A_BUTTON_LEFT) && (*semaphoreA == 1) && (dir_enableA != DISABLE_BOTH) && (dir_enableA != DISABLE_LEFT))
	{
		run_motorA(MOVE_LEFT);
		*semaphoreA = 0;
	}
	else if (!HAL_GPIO_ReadPin(GPIOA, MOTOR_A_BUTTON_RIGHT) && !HAL_GPIO_ReadPin(GPIOA, MOTOR_A_BUTTON_LEFT)) 
	{
		stop_motorA();
		*semaphoreA = 1;
	}	
}
	

/* Read buttons and run the motor if;
 *			- button is pressed & motor is not running(semaphore) & the desired direction IS enabled 
 * stop motor if;
 * 			- any of the previous is FALSE */
void read_button_motorB(int* semaphoreB){
	if(HAL_GPIO_ReadPin(GPIOF, MOTOR_B_BUTTON_RIGHT) && (*semaphoreB == 1) && (dir_enableB != DISABLE_BOTH) && (dir_enableB != DISABLE_RIGHT))
	{
		run_motorB(MOVE_RIGHT);
		*semaphoreB = 0;
	}
	if(HAL_GPIO_ReadPin(GPIOF, MOTOR_B_BUTTON_LEFT) && (*semaphoreB == 1) && (dir_enableB != DISABLE_BOTH) && (dir_enableB != DISABLE_LEFT))
	{
		run_motorB(MOVE_LEFT);
		*semaphoreB = 0;
	}
	else if (!HAL_GPIO_ReadPin(GPIOF, MOTOR_B_BUTTON_RIGHT) && !HAL_GPIO_ReadPin(GPIOF, MOTOR_B_BUTTON_LEFT)) 
	{
		stop_motorB();
		*semaphoreB = 1;
	}	
}

/* Read buttons and run the motor if;
 *			- button is pressed & motor is not running(semaphore) & the desired direction IS enabled 
 * stop motor if;
 * 			- any of the previous is FALSE */
void read_button_motorC(int* semaphoreC){
	if(HAL_GPIO_ReadPin(GPIOG, MOTOR_C_BUTTON_RIGHT) && (*semaphoreC == 1) && (dir_enableC != DISABLE_BOTH) && (dir_enableC != DISABLE_RIGHT))
	{
		run_motorC(MOVE_RIGHT);
		*semaphoreC = 0;
	}
	if(HAL_GPIO_ReadPin(GPIOG, MOTOR_C_BUTTON_LEFT) && (*semaphoreC == 1) && (dir_enableC != DISABLE_BOTH) && (dir_enableC != DISABLE_LEFT))
	{
		run_motorC(MOVE_LEFT);
		*semaphoreC = 0;
	}
	else if (!HAL_GPIO_ReadPin(GPIOG, MOTOR_C_BUTTON_RIGHT) && !HAL_GPIO_ReadPin(GPIOG, MOTOR_C_BUTTON_LEFT)) 
	{
		stop_motorC();
		*semaphoreC = 1;
	}	
}

/* Read buttons and run actuator to the desired direction */
void read_button_actuator(void)
{
	if(HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_8))
	{
		run_actuator(MOVE_RIGHT);
	}
	
	else if(HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_9))
	{
		run_actuator(MOVE_LEFT);
	}
	else
	{	
		stop_actuator();
	}
}
