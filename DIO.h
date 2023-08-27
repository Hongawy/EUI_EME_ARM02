/*
 * DIO.h
 *
 *  Created on: Aug 13, 2023
 *      Author: Mina Adel
 */

#ifndef DIO_H_
#define DIO_H_
#include "tm4c123gh6pm.h"
#include "bitwise_operation.h"
#include "data_types.h"
/********************************************ENUMS******************************************************/

typedef enum
{
    PORTA,
    PORTB,
    PORTC,
    PORTD,
    PORTE,
    PORTF
}PORT_NAME;

/*************************************FUNCTIONS DECLARATION********************************************/
/**DIO_Init: FUNCTION THAT INITIALIZES THE PORT WITH THE REQUIRED INPUT AND OUTPUT PINS**/
void DIO_Init(PORT_NAME,uint8_t OUTPUT_PINS,uint8_t INPUTS_PINS);
/**DIO_WritePin: FUNCTION THAT SETS A SPECIFIC PIN WITH THE GIVEN VALUE**/
void DIO_WritePin(PORT_NAME,uint8_t PIN,uint8_t VALUE);
/**DIO_WritePort: FUNCTION THAT SETS AN ENTIRE PORT**/
void DIO_ReadPin(PORT_NAME,uint8_t PIN);


#endif /* DIO_H_ */
