/*
 * bitwise_operation.h
 *
 *  Created on: Aug 13, 2023
 *      Author: Mina Adel
 */

#ifndef BITWISE_OPERATION_H_
#define BITWISE_OPERATION_H_

#define SET_BIT(PORT,BIT)   (PORT|=(1<<BIT))
#define CLEAR_BIT(PORT,BIT) (PORT&=~(1<<BIT))
#define GET_BIT(PORT,BIT)   ((PORT&(1<<BIT))>>BIT)
#define TOGGLE_BIT(PORT,BIT)    (PORT^=(1<<BIT))



#endif /* BITWISE_OPERATION_H_ */
