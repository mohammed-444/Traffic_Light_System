


#ifndef APP_H_
#define APP_H_

#include "../ECUAL/LED/LED.h"
#include "../MCUAL/EXT_INTERRUPT/EXT_INTTERUPT.h"
#include "../MCUAL/TIMER0/TIMER0.h"
/********************************************************************
*                                Definitions
********************************************************************/
#define CAR_GREEN_PORT		PORTA_ID
#define CAR_YELLOW_PORT		PORTA_ID
#define CAR_RED_PORT		PORTA_ID

#define CAR_GREEN_PIN		PIN0_ID
#define CAR_YELLOW_PIN		PIN1_ID
#define CAR_RED_PIN			PIN2_ID


#define PEDESTRAIN_GREEN_PORT		PORTB_ID
#define PEDESTRAIN_YELLOW_PORT		PORTB_ID
#define PEDESTRAIN_RED_PORT			PORTB_ID

#define PEDESTRAIN_GREEN_PIN		PIN0_ID
#define PEDESTRAIN_YELLOW_PIN		PIN1_ID
#define PEDESTRAIN_RED_PIN			PIN2_ID




#define TOTAL_DELAY	5000	/*in ms the time it take to switch leds*/
#define DELAY_UNIT	250			/*the delay step each time to reach the total delay*/

#define TOTAL_DELAY_COUNT	(TOTAL_DELAY/DELAY_UNIT)
#define	BLINK_RATIO			(2)		/*the time when we want to toggle the led state */

typedef enum
{	
	red = 0 ,
	yellow = 1 ,
	green = 2
}light_state;

// if there is any error in the inlialization the programm will terminate
uint8_t app_error;
// store the previous states of the car light 
light_state car_prev_state;
light_state car_current_state;
// store the previous states of the pedestrain light 
light_state pedestrain_prev_state;
light_state pedestrain_current_state;
// counter to count the number of DELAY_UNIT counted
uint8_t timer_counter;
// interrupt flag being high when interrupt trigger
uint8_t int_flag ;
/********************************************************************************************************
*                                                  Prototypes
********************************************************************************************************/




/***********************************************************************************
*                                application initialization
*************************************************************************************/

/*only called once to initialize the led pin ,timer and interrupt config */
void APP_init(void);
/***********************************************************************************
*                                application Scheduler
*************************************************************************************/
//the main idea is that it make small delay every time the eye can not catch then retrun back from the state to the 
// scheduler to check if there is no change in the programm 

/*the Scheduler is a simple implementation of operating system 
first the scheduler chech if there is any error in the initialization function with app_error flag
then it check if the timer counter reach the specified time to change the state condition
then from the previous states it decide the next state it will go to */
void APP_Scheduler(void);
/***********************************************************************************
*                       car green on & pedestrain red on
*************************************************************************************/
void State1(void);
/***********************************************************************************
*                         car yellow on & pedestrain red on
*************************************************************************************/
void State2(void);
/***********************************************************************************
*                          car red on & pedestrain red on
*************************************************************************************/
void State3(void);
/***********************************************************************************
*                           car red on & pedestrain green on
*************************************************************************************/
void State4(void);
/***********************************************************************************
*                          car yellow on & pedestrain yellow on
*************************************************************************************/
void State5(void);
/***********************************************************************************
*                                clear state
*************************************************************************************/
/*turn all led pins off*/
void Clear_States(void);



#endif /* APP_H_ */