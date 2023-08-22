


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





uint8_t app_error;

light_state car_prev_state;
light_state car_current_state;

light_state pedestrain_prev_state;
light_state pedestrain_current_state;

uint8_t timer_counter;

uint8_t int_flag ;
/*********************************************************
*               Prototypes
*********************************************************/

void APP_init(void);

void APP_Scheduler(void);

void State1(void);
void State2(void);
void State3(void);
void State4(void);
void State5(void);

void Clear_States(void);



#endif /* APP_H_ */