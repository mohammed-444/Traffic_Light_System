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
uint8_t break_delay = 0; 

timer_error_state TIMER0_Delay_ms(uint32_t T_delay)
{
	break_delay = 0;
	uint32_t T_tick = prescaler;
	T_tick = (prescaler * 1000000) / (F_CPU_MCU);
	uint32_t T_maxdelay = T_tick * 256;
	if(T_delay < T_maxdelay)
	{
		uint8_t T_initialvalue = ( (T_maxdelay - T_delay) / T_tick );
		TCNT0 = T_initialvalue; //set TCNT0 with initial value
		while(! BIT_IS_SET(TIFR,0)); //check bit TOV0 is set that mean overflow occur
		SET_BIT(TIFR,0); //as not using interrupt should set this bit to clear flag
	}
	else if(T_delay > T_maxdelay)
	{
		uint8_t NUM_overflow = (T_delay / T_maxdelay) + 1;
		uint8_t T_initialvalue =  ( 256 - ( ( T_delay / T_tick ) / NUM_overflow ) ) ;
		uint8_t actaul_counted_overflow = 0 ;
		while(actaul_counted_overflow < NUM_overflow)
		{
			TCNT0 = T_initialvalue; //set TCNT0 with initial value
			while(! BIT_IS_SET(TIFR,0)); //check bit TOV0 is set that mean overflow occur
			SET_BIT(TIFR,0); //as not using interrupt should set this bit to clear flag
			actaul_counted_overflow++;
			if (break_delay == 1)
			break;
		}
	}
	return t_ok;
	
}

timer_error_state TIMER0_endDelay(void)
{
	break_delay = 1;
	return t_ok;
}