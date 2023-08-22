/******************************************
* Module: LED
*
* File Name: LED.c
*
* Description: source file for AVR LED Driver
*
* Author: Mohammed Alaa
*
******************************************/
#include "LED.h"
uint8_t stop_blink = 0;
/*********************************************************
*               Implement
*********************************************************/
error_state LED_blink(uint8_t PORT_X , uint8_t PIN_NUM,uint8_t time_of_blinking)
{
	stop_blink = 0;
	uint8_t num_of_iterate = time_of_blinking  ;
	while(num_of_iterate  > 0)
	{
		LED_on(PORT_X,PIN_NUM);
		TIMER0_Delay_ms(499900);
		if( stop_blink == 1)
		break;
		LED_off(PORT_X,PIN_NUM);
		TIMER0_Delay_ms(499900);
		if( stop_blink == 1)
		break;
		num_of_iterate--;
	}
}

error_state LED_stopBlink(void)
{
	stop_blink = 1;
	return TIMER0_endDelay();
	
}

error_state LED_blinkForTwoPins(uint8_t PORT_X_1 , uint8_t PIN_NUM_1,uint8_t PORT_X_2 , uint8_t PIN_NUM_2,uint8_t time_of_blinking)
{
	error_state error0;
	stop_blink = 0;
	uint8_t num_of_iterate = time_of_blinking  ;
	while(num_of_iterate  > 0)
	{
		error0=LED_on(PORT_X_1,PIN_NUM_1);
		LED_on(PORT_X_2,PIN_NUM_2);
		TIMER0_Delay_ms(499900);// 499.9ms
		if( stop_blink == 1)
		break;
		LED_off(PORT_X_1,PIN_NUM_1);
		error0=LED_off(PORT_X_2,PIN_NUM_2);
		TIMER0_Delay_ms(499900);
		if( stop_blink == 1)
		break;
		num_of_iterate--;
	}
	return error0;
}