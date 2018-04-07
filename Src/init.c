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
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, DIR);
		htim2.Init.Period = 5000;
		HAL_TIM_PWM_Init(&htim2); 
		setDirA = 1;
	}
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
}

/* Init motorB with the given DIRection
 * and runs the motor. If DIR is already set, 
 * then just run */
void run_motorB(int DIR){
	if(!setDirB)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, DIR);
		htim2.Init.Period = 5000;
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
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_12, DIR);
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_13, GPIO_PIN_RESET); // enable
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_14, GPIO_PIN_RESET);
		htim2.Init.Period = 5000;
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

/* Init motorA and reset the DIRection */
void init_motorA(void){
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);		//DIR
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_SET);	//ENABLE
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_RESET);//COM
	setDirA = 0;
}

/* Init motorB and reset the DIRection */
void init_motorB(void){
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);	//DIR
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_SET);	//ENABLE
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_RESET);//COM
	setDirB = 0;
}

/* Init motorC and reset the DIRection */
void init_motorC(void){
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_12, GPIO_PIN_SET);	//DIR
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_13, GPIO_PIN_SET);	//ENABLE
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_14, GPIO_PIN_RESET);//COM
	setDirC = 0;
}


/* Read buttons and run the motor if;
 *			- button is pressed & motor is not running(semaphore) & the desired direction IS enabled 
 * stop motor if;
 * 			- any of the previous is FALSE */
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
	

/* Read buttons and run the motor if;
 *			- button is pressed & motor is not running(semaphore) & the desired direction IS enabled 
 * stop motor if;
 * 			- any of the previous is FALSE */
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

/* Read buttons and run the motor if;
 *			- button is pressed & motor is not running(semaphore) & the desired direction IS enabled 
 * stop motor if;
 * 			- any of the previous is FALSE */
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

/* Read buttons and run actuator to the desired direction */
void read_button_actuator(void)
{
	if(HAL_GPIO_ReadPin(GPIOH, GPIO_PIN_0))
	{
		 run_actuator(GPIO_PIN_SET);
	}
	
	else if(HAL_GPIO_ReadPin(GPIOH, GPIO_PIN_1))
	{
		 run_actuator(GPIO_PIN_RESET);
	}
	else
		stop_actuator();
}

/* Switches the LED ON on the board. Use it for debug. */
void ledON(void){
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_SET);	
}

/* Switches the LED OFF on the board. Use it for debug. */
void ledOFF(void){
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_RESET);
}

/* Use the predefined "send" variable from main.c
 * char[20] send = {0};
 * sprintf(send, "hello world");
 * To use this:SendToPC((uint8_t*) send, sizeof(send))*/
void SendToPC(uint8_t* send, size_t length)
{
	HAL_UART_Transmit_IT(&huart1, (uint8_t*)send, length); 
	HAL_UART_Transmit_IT(&huart1, (uint8_t*)"\n\r", 2);
}


