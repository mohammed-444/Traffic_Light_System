/******************************************
* Module: LED
*
* File Name: LED.h
*
* Description: header file for AVR LED Driver
*
* Author: Mohammed Alaa
*
******************************************/


#ifndef LED_H_
#define LED_H_

#include "../../MCUAL/DIO/DIO.h"
#include "../../MCUAL/TIMER0/TIMER0.h"


/*********************************************************
*               Prototypes
*********************************************************/

/*
* Description:
* set pin for specific port as output pin to be able to connect led

void LED_init(uint8_t PORT_X , uint8_t PIN_NUM);

/*
* Description:
* set pin high to turn led on if connected as active high or turn led off if connected as active low
*/
error_state LED_on(uint8_t PORT_X , uint8_t PIN_NUM);

/*
* Description:
* Clear pin high to turn led off if connected as active high or turn led on if connected as active low
*/
error_state LED_off(uint8_t PORT_X , uint8_t PIN_NUM);

/*
* Description:
* Toggle pin
*/
error_state LED_toggle(uint8_t PORT_X , uint8_t PIN_NUM);


/*
* Description:
* will set pin high for half second then low for half second and will repeat it for number of times
*/
error_state LED_blink(uint8_t PORT_X , uint8_t PIN_NUM,uint8_t time_of_blinking);

/*
* Description:
* will set pin high for half second then low for half second and will repeat it for number of times
*/
error_state LED_blinkForTwoPins(uint8_t PORT_X_1 , uint8_t PIN_NUM_1,uint8_t PORT_X_2 , uint8_t PIN_NUM_2,uint8_t time_of_blinking);

/*
* Description:
* this function stop blinking  as call function timer0_endDelay(as end loop doing to make specific delay wanted)
*/
error_state LED_stopBlink(void);

#endif /* LED_H_ */