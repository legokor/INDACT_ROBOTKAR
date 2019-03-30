#include "init.h"

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
UART_HandleTypeDef huart1;


/* Init motorA and reset the DIRection */
void init_motorA(void){
	HAL_GPIO_WritePin(GPIOC, MOTOR_A_DIR_PIN, GPIO_PIN_SET);		//DIR
	HAL_GPIO_WritePin(GPIOC, MOTOR_A_ENALBE_PIN, GPIO_PIN_SET);	//ENABLE
	HAL_GPIO_WritePin(GPIOC, MOTOR_A_COM_PIN, GPIO_PIN_RESET);  //COM
	setDirA = 0;
}

/* Init motorB and reset the DIRection */
void init_motorB(void){
	HAL_GPIO_WritePin(GPIOC, MOTOR_B_DIR_PIN, GPIO_PIN_SET);		//DIR
	HAL_GPIO_WritePin(GPIOC, MOTOR_B_ENALBE_PIN, GPIO_PIN_SET);	//ENABLE
	HAL_GPIO_WritePin(GPIOC, MOTOR_B_COM_PIN, GPIO_PIN_RESET);	//COM
	setDirB = 0;
}

/* Init motorC and reset the DIRection */
void init_motorC(void){
	HAL_GPIO_WritePin(GPIOF, MOTOR_C_DIR_PIN, GPIO_PIN_SET);		//DIR
	HAL_GPIO_WritePin(GPIOF, MOTOR_C_ENALBE_PIN, GPIO_PIN_RESET);	//ENABLE
	HAL_GPIO_WritePin(GPIOF, MOTOR_C_COM_PIN, GPIO_PIN_RESET);	//COM
	setDirC = 0;
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


