/*
 * systick_timer.c
 *
 *  Created on: Aug 24, 2023
 *      Author: Mina Adel Attia
 */
/************************INCLUDED FILES******************/
#include "systick_timer.h"
#include "tm4c123gh6pm.h"
/************************FUNCTIONS DEFINITIONS*******************/
/**Function Name: ST_Init
 * Function Description:
 * Initializes the SysTick Timer with the required configurations
 * Inputs: uint8_t CLK_SRC clock source
 *         uint8_t INT_EN  Interrupt enable
 * Output: void**/
void ST_Init(void){
/**CLEAR THE ENABLE PIN BEFORE CONFIGURING THE TIMER**/
    ST_DeInit();
/**INTERRUPT ENABLE PIN CONFIGURATION**/
#if (INT_EN == ENABLE)
    SET_BIT(NVIC_ST_CTRL_R,1);
#elif (INT_EN == DISABLE)
    CLEAR_BIT(NVIC_ST_CTRL_R,1);
#endif
/**CLOCK SOURCE PIN CONFIGURATION**/
#if (CLK_SRC==ENABLE)
    SET_BIT(NVIC_ST_CTRL_R,2);
#elif (CLK_SRC==DISABLE)
    CLEAR_BIT(NVIC_ST_CTRL_R,2);
#endif
/**ENABLE PIN CONFIGURATION**/
#if (EN==ENABLE)
    SET_BIT(NVIC_ST_CTRL_R,0);
#elif (EN==DISABLE)
    CLEAR_BIT(NVIC_ST_CTRL_R,0);
#endif
}
/**Function Name: ST_SetReloadValue
 * Function Description:
 * Sets the Reload Value of the Timer.
 *         Inputs: uint32_t RELOAD_VAL
 *         Output: void**/
void ST_SetReloadValue(uint32_t RELOAD_VAL){
    NVIC_ST_RELOAD_R=RELOAD_VAL;
}
/**Function Name: ST_DeInit
 * Function Description:
 * Clears the SysTick Timer Enable Pin.
 *         Inputs: void
 *         Output: void**/
void ST_DeInit(void){
    CLEAR_BIT(NVIC_ST_CTRL_R,0);
}

