
/*
 * LED.c
 *
 ModuleName: LED
 Author: Ahmedmohamed
 Purpose: Source file for LED Driver
 */

/**************************************************************Includes*********************************************************************/

#include "LED.h"


/*******************************************************Functions Definitions**********************************************************/

/***************************************************************
Function Name   : LED_config
Inputs          : void
Outputs         : void
Reentrancy      : Reentrancy
Synchronous     : Synchronous
Description     : Initialize all of the leds
 ****************************************************************/

void LED_config(void)
{

    /* Enable the GPIO Port F*/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)){
        SYSTICK_currentState = ERROR_GPIO;
    }

    /* Configure PF1 (Red LED)*/
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, RED_LED | BLUE_LED |GREEN_LED );
    if (!(HWREG(GPIO_PORTF_BASE + GPIO_O_DIR) & RED_LED  )) {
        // PF2 not set as output
        while (1) {
            SYSTICK_currentState = ERROR_INPUTLED;
        }
    }



}


/***************************************************************
Function Name   : LED_blueLight
Inputs          : void
Outputs         : void
Reentrancy      : Reentrant
Synchronous     : ASynchronous
Description     : Turn on blue led
 ****************************************************************/

void LED_blueLight(void)
{
    GPIOPinWrite(GPIO_PORTF_BASE, RED_LED,  OFF); // Turn on LED
    GPIOPinWrite(GPIO_PORTF_BASE, BLUE_LED, BLUE_LED); // Turn on LED
    GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED, OFF); // Turn on LED

}



/***************************************************************
Function Name   : LED_greenLight
Inputs          : void
Outputs         : void
Reentrancy      : Reentrant
Synchronous     : ASynchronous
Description     : Turn on green led
 ****************************************************************/

void LED_greenLight(void)
{
    GPIOPinWrite(GPIO_PORTF_BASE, RED_LED,  OFF); // Turn on LED
    GPIOPinWrite(GPIO_PORTF_BASE, BLUE_LED, OFF); // Turn on LED
    GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED, GREEN_LED); // Turn on LED

}


/***************************************************************
Function Name   : LED_redLight
Inputs          : void
Outputs         : void
Reentrancy      : Reentrant
Synchronous     : ASynchronous
Description     : Turn on red led
 ****************************************************************/

void LED_redLight(void)
{
    GPIOPinWrite(GPIO_PORTF_BASE, RED_LED, RED_LED); // Turn on LED
    GPIOPinWrite(GPIO_PORTF_BASE, BLUE_LED, OFF); // Turn on LED
    GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED, OFF); // Turn on LED

}


/***************************************************************
Function Name   : LED_whiteLight
Inputs          : void
Outputs         : void
Reentrancy      : Reentrant
Synchronous     : ASynchronous
Description     : Turn on white led
 ****************************************************************/

void LED_whiteLight(void)
{
    GPIOPinWrite(GPIO_PORTF_BASE, RED_LED, RED_LED); // Turn on LED
    GPIOPinWrite(GPIO_PORTF_BASE, BLUE_LED, BLUE_LED); // Turn on LED
    GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED, GREEN_LED); // Turn on LED

}
/***************************************************************
Function Name   : LEDS_off
Inputs          : void
Outputs         : void
Reentrancy      : Reentrant
Synchronous     : ASynchronous
Description     : Turn off All leds
 ****************************************************************/
void LEDS_off(void)
{
    GPIOPinWrite(GPIO_PORTF_BASE, RED_LED, 0x00); // Turn on LED
    GPIOPinWrite(GPIO_PORTF_BASE, BLUE_LED, 0x00); // Turn on LED
    GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED, 0x00); // Turn on LED
}
