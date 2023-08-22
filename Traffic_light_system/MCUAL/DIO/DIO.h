/******************************************
* Module: DIO(GPIO)
*
* File Name: DIO.h
*
* Description: header file for AVR DIO Driver
*
* Author: Mohammed Alaa
*
******************************************/

#ifndef DIO_H_
#define DIO_H_

#include "../../utilities/std_types.h"
#include "../../utilities/MCU_register.h"
#include "../../utilities/common_macros.h"

/********************************************************************
*                                Definitions
********************************************************************/
#define NUM_OF_PORT 4
#define NUM_OF_PIN_PER_PORT 8 

#define PORTA_ID   0
#define PORTB_ID   1
#define PORTC_ID   2
#define PORTD_ID   3   

#define PIN0_ID    0
#define PIN1_ID    1
#define PIN2_ID    2
#define PIN3_ID    3
#define PIN4_ID    4
#define PIN5_ID    5
#define PIN6_ID    6
#define PIN7_ID    7

#define LOGIC_HIGH   (1u)
#define LOGIC_LOW    (0u)
        


#define INPUT_PIN 0
#define INPUT_PIN_PULLUP 1
#define OUTPUT_PIN 2

typedef enum{
	
	ok,error
	
	}error_state;

/*********************************************************
*               Prototypes
*********************************************************/


/*
* Description:
* setup direction of specific pin in port input/input&pull up/output
*/
error_state DIO_setupPinDirection(uint8_t PORT_X ,uint8_t PIN_NUM,uint8_t DIRECTION );

/*
* Description:
* write value logic high or low in specific pin
*/
error_state DIO_writePin(uint8_t PORT_X ,uint8_t PIN_NUM,uint8_t value );

/*
* Description:
* read and return value for specific pin, it should be logic high or low
*/
uint8_t DIO_readPin(uint8_t PORT_X ,uint8_t PIN_NUM);

/*
* Description:
* toggle value for specific pin*/
error_state DIO_togglePin(uint8_t PORT_X ,uint8_t PIN_NUM);


#endif /* DIO_H_ */