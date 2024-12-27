/*
 * LED.h
 *
 *      ModuleName: LED
 *      Author: Ahmedmohamed
 *      Purpose: Header file for LED Driver
 */

#ifndef LED_H_
#define LED_H_

/********************************************Includes*********************************/
#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"

/********************************************Definitions and Macros*********************************/

#define RED_LED     GPIO_PIN_1
#define BLUE_LED    GPIO_PIN_2
#define GREEN_LED   GPIO_PIN_3
#define OFF             0

/********************************************functions prototypes*********************************/

void LED_config(void);
void LED_blueLight(void);
void LED_greenLight(void);
void LED_redLight(void);
void LED_whiteLight(void);
void LEDS_off(void);





#endif /* LED_H_ */
