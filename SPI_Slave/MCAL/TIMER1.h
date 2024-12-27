/*
 * TIMER1.h
 *
 *      ModuleName: Timer1
 *      Author: Ahmed Mohamed
 *      Purpose: Header file for Timer1 Driver
 */
#ifndef MCAL_TIMER1_H_
#define MCAL_TIMER1_H_


/***************************************************Includes*************************************/

#include <stdbool.h>
#include <stdint.h>
#include <stdbool.h>


#include "driverlib/timer.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/ssi.h"


#include "inc/hw_gpio.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"



/*******************************************Shared Global Variables(extern)***********************************/
extern uint8_t TIMER1_delayFlag;

/************************************************functions prototypes*****************************************/
void TIMER1_delayMsecInterrupt(uint32_t a_delayInMsec);
void TIMER1_start(void);
void TIMER1_clear(uint32_t a_delayInMsec);

#endif /* MCAL_TIMER1_H_ */
