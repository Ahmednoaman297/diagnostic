/*
 * BTN.h
 *
 *      ModuleName: BTN
 *      Author: Ahmedmohamed
 *      Purpose: Header file for BTN Driver
 */

#ifndef BTN_H_
#define BTN_H_

/*************************************************************Includes**************************************************************/
#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"

#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/pin_map.h"
#include "driverlib/interrupt.h"

#include "../MCAL/Timer0.h"

/*******************************************************Definitions and Macros**********************************************************/
#define BTN_0           GPIO_PIN_0
#define BTN_4           GPIO_PIN_4
#define ERROR_CLOCKWISE    0x15

#ifndef GPIO_LOCK_KEY
#define GPIO_LOCK_KEY   0x4C4F434B
#endif


/*******************************************************Function Prototypes**********************************************************/
void BTN_init (void);
uint8_t BTN_read (uint8_t a_btn ,uint32_t a_port);

#endif /* BTN_H_ */
