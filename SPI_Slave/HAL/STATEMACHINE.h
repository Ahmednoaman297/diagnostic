
/*
 * STATEMACHINE.h
 *
 ModuleName: STATEMACHINE
 Author:     Ahmed Mohamed
 Purpose:    Header file for STATEMACHINE Driver
 */
#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_

/********************************************Includes*********************************/
#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"

#include "LED.h"

#include "../MCAL/SYSTICK.h"
#include "../MCAL/Timer0.h"
#include "../MCAL/TIMER1.h"



/******************************************Definitions and Macros*********************************/
#define CW              1
#define CCW             2
#define INTIAL_STATE    3
#define IDLE           0x06
#define ERROR_STATE    0x09
#define RED_LED      GPIO_PIN_1
#define BLUE_LED     GPIO_PIN_2
#define GREEN_LED    GPIO_PIN_3

/********************************************functions prototypes*********************************/
void CounterClockwise (void);
void Clockwise (void);
void Initial_State (void);
void idle_state(void);

#endif /* STATEMACHINE_H_ */
