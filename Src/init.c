#include "init.h"

volatile int dir_enableA = ENABLE_BOTH;
volatile int dir_enableB = ENABLE_BOTH;
volatile int dir_enableC = ENABLE_BOTH;

void run_motorA(int DIR){
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, DIR);
	htim2.Init.Period = 5000;
	HAL_TIM_PWM_Init(&htim2); 
}

void run_motorB(int DIR){
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, DIR);
	htim2.Init.Period = 5000;
	HAL_TIM_PWM_Init(&htim2); 
}

void run_motorC(int DIR){
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_12, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_13, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_14, DIR);
	htim2.Init.Period = 5000;
	HAL_TIM_PWM_Init(&htim2); 
}

void stop_motorA(){
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_RESET);	// reset motor ENABLE
	HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_2);
}

void stop_motorB(){
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_RESET);	// reset motor ENABLE
	HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_3);
}

void stop_motorC(){
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_13, GPIO_PIN_RESET);	// reset motor ENABLE
	HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_4);
}

void init_motorA(void){
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_RESET);
}

void init_motorB(void){
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_RESET);
}

void init_motorC(void){
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_12, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_13, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_14, GPIO_PIN_RESET);
}



void read_button_motorA(int* semaphoreA){
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_13) && (*semaphoreA == 1) && (dir_enableA != DISABLE_BOTH) && (dir_enableA != DISABLE_RIGHT))
	{
		run_motorA(GPIO_PIN_RESET);
		*semaphoreA = 0;
	}
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_14) && (*semaphoreA == 1) && (dir_enableA != DISABLE_BOTH) && (dir_enableA != DISABLE_LEFT))
	{
		run_motorA(GPIO_PIN_SET);
		*semaphoreA = 0;
	}
	else if (!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_13) && !HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_14)) 
	{
		stop_motorA();
		*semaphoreA = 1;
	}	
}
	

void read_button_motorB(int* semaphoreB){
	if(HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_3) && (*semaphoreB == 1) && (dir_enableB != DISABLE_BOTH) && (dir_enableB != DISABLE_RIGHT))
	{
		run_motorB(GPIO_PIN_RESET);
		*semaphoreB = 0;
	}
	if(HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_4) && (*semaphoreB == 1) && (dir_enableB != DISABLE_BOTH) && (dir_enableB != DISABLE_LEFT))
	{
		run_motorB(GPIO_PIN_SET);
		*semaphoreB = 0;
	}
	else if (!HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_3) && !HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_4)) 
	{
		stop_motorB();
		*semaphoreB = 1;
	}	
}

void read_button_motorC(int* semaphoreC){
	if(HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_0) && (*semaphoreC == 1) && (dir_enableC != DISABLE_BOTH) && (dir_enableC != DISABLE_RIGHT))
	{
		run_motorC(GPIO_PIN_RESET);
		*semaphoreC = 0;
	}
	if(HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_1) && (*semaphoreC == 1) && (dir_enableC != DISABLE_BOTH) && (dir_enableC != DISABLE_RIGHT))
	{
		run_motorC(GPIO_PIN_SET);
		*semaphoreC = 0;
	}
	else if (!HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_0) && !HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_1)) 
	{
		stop_motorC();
		*semaphoreC = 1;
	}	
}

void ledON(void){
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_SET);	
}

void ledOFF(void){
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_RESET);
}



