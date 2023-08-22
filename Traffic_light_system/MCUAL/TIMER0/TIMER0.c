/******************************************************************************
 *
 * Module: TIMER0
 *
 * File Name: timer0.c
 *
 * Description: source file for the AVR timer0 driver
 *
 * Author: Mohammed Alaa
 *
 *******************************************************************************/	
#include "TIMER0.h"






timer_error_state TIMER0_init()
{	/*choose normal mode*/
	TCCR0 |= ((1<<7));
	TCCR0 |= ((1<<0) | (1<<2)); /*  choose clock   1024      */	
	return t_ok;
}


 timer_error_state TIMER0_stop(void)
 {
	 TCCR0 = 0x00; /* to make no clock source        */
	 return t_ok;
 }