#include "APP.h"

// if there is any error in the inlialization the programm will terminate
uint8_t app_error =	LOGIC_LOW;

// store the previous states of the car light 
light_state car_prev1_state = yellow;
light_state car_prev2_state = green;
light_state car_current_state = red;
// store the previous states of the pedestrain light 
light_state pedestrain_prev1_state = yellow;
light_state pedestrain_prev2_state = green;
light_state pedestrain_current_state = red;
// counter to count the number of DELAY_UNIT counted
uint8_t timer_counter = 0;
// interrupt flag being high when interrupt trigger
uint8_t int_flag = LOGIC_LOW;



/***********************************************************************************
*                                external interrupt handler
*************************************************************************************/

/*if the interrupt flag or the pedestrain current state is green then do nothing
else update the previous state of the traffic light for the car and pedestrain 
then clear the counter and state and raise the interrupt flag*/
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

/***********************************************************************************
*                                application initialization
*************************************************************************************/

/*only called once to initialize the led pin ,timer and interrupt config */
void APP_init(void)
{
	/*initialize led for car & pedestrian and test if the led init function return an error*/
	if (LED_init(CAR_RED_PORT,CAR_RED_PIN)) app_error=LOGIC_HIGH;

	LED_init(CAR_GREEN_PORT,CAR_GREEN_PIN);
	LED_init(CAR_YELLOW_PORT,CAR_YELLOW_PIN);
	LED_init(PEDESTRAIN_RED_PORT,PEDESTRAIN_RED_PIN);
	LED_init(PEDESTRAIN_GREEN_PORT,PEDESTRAIN_GREEN_PIN);
	LED_init(PEDESTRAIN_YELLOW_PORT,PEDESTRAIN_YELLOW_PIN);
	
	/*initialize the timer with the config and test if the timer init function return an error*/
	if(TIMER0_init()) app_error=LOGIC_HIGH;
	
	/*ENABLE GLOBAL Interrupt*/
	GLOBAL_INTERRUPT_ENABLE();
	
	/*initialize the external interrupt 0 with the config and test if the int0 init function return an error*/
	if(INT0_init(FALLING_EDGE_TRIGGER,INPUT_PIN_PULLUP)) app_error=LOGIC_HIGH;
		
}
/***********************************************************************************
*                                application Scheduler
*************************************************************************************/
//the main idea is that it make small delay every time the eye can not catch then retrun back from the state to the 
// scheduler to check if there is no change in the program 

/*the Scheduler is a simple implementation of operating system 
first the scheduler chech if there is any error in the initialization function with app_error flag
then it check if the timer counter reach the specified time to change the state condition
then from the previous states it decide the next state it will go to */
void APP_Scheduler(void)
{
	/*the super loop*/
	while (1)
	{	
		/*first the scheduler chech if there is any error in the initialization function with app_error flag*/
		if (app_error == LOGIC_HIGH)
		{
			break;
		}
		
		/*it check if the timer counter reach the specified time to change the state condition*/
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
			/*from the previous states it decide the next state it will go to */
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

/***********************************************************************************
*                                clear state
*************************************************************************************/
/*turn all led pins off*/
void Clear_States(void)
{
	LED_off(CAR_RED_PORT,CAR_RED_PIN);
	LED_off(CAR_GREEN_PORT,CAR_GREEN_PIN);
	LED_off(CAR_YELLOW_PORT,CAR_YELLOW_PIN);
	
	LED_off(PEDESTRAIN_RED_PORT,PEDESTRAIN_RED_PIN);
	LED_off(PEDESTRAIN_GREEN_PORT,PEDESTRAIN_GREEN_PIN);
	LED_off(PEDESTRAIN_YELLOW_PORT,PEDESTRAIN_YELLOW_PIN);
}
/***********************************************************************************
*                       car green on & pedestrain red on
*************************************************************************************/
void State1(void)
{
	pedestrain_current_state = red;
	car_current_state = green;
	
	LED_on(CAR_GREEN_PORT,CAR_GREEN_PIN);
	LED_on(PEDESTRAIN_RED_PORT,PEDESTRAIN_RED_PIN);
	
	TIMER0_Delay_ms(DELAY_UNIT);
	timer_counter++;
	
}
/***********************************************************************************
*                         car yellow on & pedestrain red on
*************************************************************************************/
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
/***********************************************************************************
*                          car red on & pedestrain red on
*************************************************************************************/
void State3(void)
{
	pedestrain_current_state = red;
	car_current_state = red;
	
	LED_on(CAR_RED_PORT,CAR_RED_PIN);
	
	LED_on(PEDESTRAIN_RED_PORT,PEDESTRAIN_RED_PIN);
	
	TIMER0_Delay_ms(DELAY_UNIT);
	
	timer_counter++;
}
/***********************************************************************************
*                           car red on & pedestrain green on
*************************************************************************************/
void State4(void)
{	
	pedestrain_current_state =green;
	car_current_state =red;
	
	
	
	LED_on(CAR_RED_PORT,CAR_RED_PIN);
	
	LED_on(PEDESTRAIN_GREEN_PORT,PEDESTRAIN_GREEN_PIN);
	
	TIMER0_Delay_ms(DELAY_UNIT);
	
	timer_counter++;
}
/***********************************************************************************
*                          car yellow on & pedestrain yellow on
*************************************************************************************/
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