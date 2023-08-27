/*
 * systick_timer.h
 *
 *  Created on: Aug 24, 2023
 *      Author: Mina Adel Attia
 */
#ifndef SYSTICK_TIMER_H_
#define SYSTICK_TIMER_H_
/**********************INCLUDED FILES****************************/
#include "bitwise_operation.h"
#include "data_types.h"

/*************************TIMER CONFIGURATIONS*******************/
#define DISABLE 0
#define ENABLE 1
#define CLK_SRC ENABLE
#define INT_EN ENABLE
#define EN DISABLE
/************************FUNCTIONS DECLARATION*******************/
/**Function Name: ST_Init
 * Function Description:
 * Initializes the SysTick Timer with the required configurations that can be accessed from the HEADER File.
 * Inputs: void
 * Output: void**/
void ST_Init(void);
/**Function Name: ST_SetReloadValue
 * Function Description:
 * Sets the Reload Value of the Timer.
 *         Inputs: uint32_t RELOAD_VAL
 *         Output: void**/
void ST_SetReloadValue(uint32_t RELOAD_VAL);
/**Function Name: ST_DeInit
 * Function Description:
 * Disables the SysTick Timer.
 *         Inputs: void
 *         Output: void**/
void ST_DeInit(void);


#endif /* SYSTICK_TIMER_H_ */
