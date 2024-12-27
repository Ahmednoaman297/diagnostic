/*
 * SYSTICK.h
 *
 *      ModuleName: SYSTICK
 *      Author: Ahmedmohamed
 *      Purpose: Header file for SYSTICK Driver
 */
#ifndef SYSTICK_H_
#define SYSTICK_H_

/***************************************************Includes***********************************************/

#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_nvic.h"

#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/interrupt.h"
#include "driverlib/systick.h"
#include "driverlib/ssi.h"

#include "SPI.h"
#include "HAL/STATEMACHINE.h"
#include "driverlib/sysctl.h"

/*******************************************************Definitions and Macros**********************************************************/

#define ERROR_SYSTICK 0x11
#define SYSTICK_ERROR_PIN       GPIO_PIN_7

/***********************************************Shared Global Variables(extern)**************************************/
extern uint8_t  SYSTICK_flag;
extern uint32_t SYSTICK_data;
extern uint8_t  SYSTICK_isr_flag;
extern uint32_t SYSTICK_currentState;
extern uint8_t  SYSTICK_flagConnection;

/**************************************************functions prototypes***********************************************/
void SYSTICK_delayMSec(uint32_t a_msec);


#endif /* SYSTICK_H_ */
