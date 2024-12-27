/*
 * Timer0.h
 *
 *      ModuleName: Timer0
 *      Author: Ahmed Mohamed
 *      Purpose: Header file for Timer0 Driver
 */


#ifndef TIMER0_H_
#define TIMER0_H_


/*************************************************************Includes**************************************************************/

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

/*******************************************************Shared Global Variable(extern)**********************************************************/
extern uint8_t Timer0_delayFlag;

/*******************************************************Function Prototypes**********************************************************/
void TIMER0_delayMsec(uint32_t a_delayInMsec);





#endif /* TIMER0_H_ */
