/******************************************
* Module: EXT_INTERRUPT
*
* File Name: EXT_INTERRUPT.c
*
* Description: source file for AVR external interrupt
*
* Author: Mohammed Alaa
*
******************************************/

#include "EXT_INTTERUPT.h"

void GLOBAL_INTERRUPT_ENABLE(void)
{
	sei();
}

void GLOBAL_INTERRUPT_DISABLE(void)
{
	cli();
}

error_state INT0_init( uint8_t triggerType,uint8_t direction)
{
	DIO_setupPinDirection(PORTD_ID,PIN2_ID,direction);/*set pin as input pin  or input pulled up*/
	MCUCR = (MCUCR & 0xFC) | triggerType;/*set type of trigger*/
	SET_BIT(GICR ,6); /*enable INT0*/
	
	return ok;
}



error_state INT0_deInit(void)
{
	CLEAR_BIT(GICR ,6);
	return ok;
}

