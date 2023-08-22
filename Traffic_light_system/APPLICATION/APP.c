#include "APP.h"

uint8_t app_error =	LOGIC_LOW;

light_state car_prev1_state = yellow;
light_state car_prev2_state = green;
light_state car_current_state = red;

light_state pedestrain_prev1_state = yellow;
light_state pedestrain_prev2_state = green;
light_state pedestrain_current_state = red;

uint8_t timer_counter = 0;

uint8_t int_flag = LOGIC_LOW;

ISR(INT0)
{
	if ((pedestrain_current_state != green) && (int_flag == LOGIC_LOW))
	{
		if (pedestrain_current_state != yellow )
		{
			pedestrain_prev2_state =pedestrain_prev1_state;
			car_prev2_state = car_prev1_state;
			
			pedestrain_prev1_state =pedestrain_current_state;
			car_prev1_state = car_current_state;
		}
		
		timer_counter = 0;
		Clear_States();
		int_flag = LOGIC_HIGH;
		
		
	}
	

}

void APP_init(void)
{
	/*initialize led for car & pedestrian*/
	if (LED_init(CAR_RED_PORT,CAR_RED_PIN)) app_error=LOGIC_HIGH;
	LED_init(CAR_GREEN_PORT,CAR_GREEN_PIN);
	LED_init(CAR_YELLOW_PORT,CAR_YELLOW_PIN);
	LED_init(PEDESTRAIN_RED_PORT,PEDESTRAIN_RED_PIN);
	LED_init(PEDESTRAIN_GREEN_PORT,PEDESTRAIN_GREEN_PIN);
	LED_init(PEDESTRAIN_YELLOW_PORT,PEDESTRAIN_YELLOW_PIN);
	
	
	if(TIMER0_init()) app_error=LOGIC_HIGH;
	
	/*ENABLE GLOBAL Interrupt*/
	GLOBAL_INTERRUPT_ENABLE();
	
	/*set INT0*/
	if(INT0_init(FALLING_EDGE_TRIGGER,INPUT_PIN_PULLUP)) app_error=LOGIC_HIGH;
		
}

void APP_Scheduler(void)
{
	
	while (1)
	{	
		if (app_error == LOGIC_HIGH)
		{
			break;
		}
		
		
		if (timer_counter == TOTAL_DELAY_COUNT)
		{
			timer_counter = 0;
			
			Clear_States();
			
			pedestrain_prev2_state =pedestrain_prev1_state;
			car_prev2_state = car_prev1_state;
			
			pedestrain_prev1_state =pedestrain_current_state;
			car_prev1_state = car_current_state;
			
			if(pedestrain_prev1_state == green)
			{
				int_flag = LOGIC_LOW;	
			}
			
			
			
		}
		else
		{
			if (((car_prev1_state == yellow) && (car_prev2_state != green) && (int_flag == LOGIC_LOW)))
			{
				State1();
			}
			else if ((((car_prev1_state == red) || (car_prev1_state == green) ) && (int_flag == LOGIC_LOW) &&(pedestrain_prev1_state == red)))
			{
				State2();
			}
			else if (((car_prev1_state == yellow) && (car_prev2_state == green) && (int_flag == LOGIC_LOW)))
			{
				State3();
			}
			else if (((car_prev1_state != red) &&(pedestrain_prev1_state == red) && (int_flag == LOGIC_HIGH)) || (pedestrain_prev1_state == green))
			{
				State5();
			}
			else if ((((pedestrain_prev1_state == red) || (pedestrain_prev1_state == yellow) ) && (int_flag == LOGIC_HIGH)))
			{
				State4();
			}
			
		}		
		
	}
	
}



void Clear_States(void)
{
	LED_off(CAR_RED_PORT,CAR_RED_PIN);
	LED_off(CAR_GREEN_PORT,CAR_GREEN_PIN);
	LED_off(CAR_YELLOW_PORT,CAR_YELLOW_PIN);
	
	LED_off(PEDESTRAIN_RED_PORT,PEDESTRAIN_RED_PIN);
	LED_off(PEDESTRAIN_GREEN_PORT,PEDESTRAIN_GREEN_PIN);
	LED_off(PEDESTRAIN_YELLOW_PORT,PEDESTRAIN_YELLOW_PIN);
}
void State1(void)
{
	pedestrain_current_state = red;
	car_current_state = green;
	
	LED_on(CAR_GREEN_PORT,CAR_GREEN_PIN);
	LED_on(PEDESTRAIN_RED_PORT,PEDESTRAIN_RED_PIN);
	
	TIMER0_Delay_ms(DELAY_UNIT);
	timer_counter++;
	
}
void State2(void)
{
	pedestrain_current_state =red;
	car_current_state =yellow;
	
	if (timer_counter%BLINK_RATIO == 0)
	{
		LED_toggle(CAR_YELLOW_PORT,CAR_YELLOW_PIN);
	}
	
	LED_on(PEDESTRAIN_RED_PORT,PEDESTRAIN_RED_PIN);
	
	TIMER0_Delay_ms(DELAY_UNIT);
	
	timer_counter++;
}
void State3(void)
{
	pedestrain_current_state = red;
	car_current_state = red;
	
	LED_on(CAR_RED_PORT,CAR_RED_PIN);
	
	LED_on(PEDESTRAIN_RED_PORT,PEDESTRAIN_RED_PIN);
	
	TIMER0_Delay_ms(DELAY_UNIT);
	
	timer_counter++;
}
void State4(void)
{	
	pedestrain_current_state =green;
	car_current_state =red;
	
	
	
	LED_on(CAR_RED_PORT,CAR_RED_PIN);
	
	LED_on(PEDESTRAIN_GREEN_PORT,PEDESTRAIN_GREEN_PIN);
	
	TIMER0_Delay_ms(DELAY_UNIT);
	
	timer_counter++;
}
void State5(void)
{
	pedestrain_current_state = yellow;
	car_current_state = yellow;
	
	if (timer_counter%BLINK_RATIO == 0)
	{
		LED_toggle(CAR_YELLOW_PORT,CAR_YELLOW_PIN);
		LED_toggle(PEDESTRAIN_YELLOW_PORT,PEDESTRAIN_YELLOW_PIN);
	}
	
	
	TIMER0_Delay_ms(DELAY_UNIT);
	
	timer_counter++;	
}