/******************************************
* Module: EXT_INTERRUPT
*
* File Name: EXT_INTERRUPT.h
*
* Description: header file for AVR external interrupt
*
* Author: Mohammed Alaa
*
******************************************/



#ifndef EXT_INTTERUPT_H_
#define EXT_INTTERUPT_H_

#include "../../utilities/common_macros.h"
#include "../../utilities/MCU_register.h"
#include "../../utilities/std_types.h"
#include "../../utilities/IVT.h"

#include "../DIO/DIO.h"

 /*******************************************************************************
 *                              Types Definition                            *
 *******************************************************************************/
 #define LOW_LEVEL_TRIGGER 0
 #define ANY_LOGIC_CHANGE_TRIGGER 1
 #define FALLING_EDGE_TRIGGER 2
 #define RISING_EDGE_TRIGGER 3

 /*******************************************************************************
 *                              Functions Prototypes                            *
 *******************************************************************************/
 
/*
* Description:
* call assembly function to enable global interrupt
*/
void GLOBAL_INTERRUPT_ENABLE(void);

/*
* Description:
* call assembly function to disable global interrupt
*/
void GLOBAL_INTERRUPT_DISABLE(void);
 
/*
* Description:
* set type of trigger first then enable EXT interrupt 0
*/
error_state INT0_init( uint8_t triggerType,uint8_t direction);



/*
* Description:
* disable EXT interrupt 0
*/
error_state INT0_deInit(void);


#endif /* EXT_INTTERUPT_H_ */