 /******************************************************************************
 *
 * Module: TIMER0
 *
 * File Name: timer0.h
 *
 * Description: Header file for the AVR timer0 driver
 *
 * Author: Mohammed Alaa
 *
 *******************************************************************************/


#ifndef TIMER_H_
#define TIMER_H_

#include "../../utilities/std_types.h"
#include "../../utilities/MCU_register.h"
#include "../../utilities/common_macros.h"
 /*******************************************************************************
 *                         Configuration                                        *
 *******************************************************************************/
#define  F_CPU_MCU  1 * 1000000
#define prescaler 1024
 
typedef enum{
	
	t_ok,t_error
	
}timer_error_state;
	
 /*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
 
  /*
 * Description : 
 * 	1. Set the required mode.
 * 	2. Set the required prescaler.
 * @argument 
 * config_Ptr : is pointer to variable contain wanted MODE & PRESCALLER
 */
 timer_error_state TIMER0_init();
 

 timer_error_state TIMER0_Delay_ms(uint32_t T_delay);
 
/*
* Description : 
* stop timer0 as make no clock source for Timer 0 peripheral
*/
 timer_error_state TIMER0_stop(void);
 
 /*
 * Description :
 * stop loop make for delay because when there is ISR during delay ,delay will cut but will continue delay so this function end delay
 */
 timer_error_state TIMER0_endDelay(void);
 
 
#endif /* TIMER_H_ */