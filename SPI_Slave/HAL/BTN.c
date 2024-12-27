
/*
 * BTN.c
 *
 ModuleName: BTN
 Author: Ahmedmohamed
 Purpose: Source file for BTN Driver
 */
/**************************************************************Includes*********************************************************************/

#include "BTN.h"

/*******************************************************Functions Definitions**********************************************************/

/***************************************************************
Function Name   : BTN_init
Inputs          : void
Outputs         : void
Reentrancy      : Reentrant
Synchronous     : ASynchronous
Description     : Initialize all of the leds
****************************************************************/

void BTN_init (void)
{
    /* Enable the GPIO Port F*/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    /*Step 3: Unlock Port F pin 0 (only required for PF0, as it is locked by default)*/
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;   /* Unlock Port F*/
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= GPIO_PIN_0;        /*Commit register for PF0*/
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;              /* Re-lock Port F*/

    /*Step 4: Configure pins 0 and 4 as input with pull-up resistors*/
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, BTN_0 | BTN_4);
    GPIOPadConfigSet(GPIO_PORTF_BASE, BTN_0 | BTN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

}


/***************************************************************
Function Name   : BTN_read
Inputs          : uint8_t a_btn
Outputs         : uint8_t switchStatus_a_btn
Reentrancy      : Reentrant
Synchronous     : ASynchronous
Description     : Return the value of the btn
****************************************************************/

uint8_t BTN_read (uint8_t a_btn)
{
    uint32_t switchStatus = GPIOPinRead(GPIO_PORTF_BASE, a_btn );
    uint8_t switchStatus_a_btn = (switchStatus & a_btn)>>a_btn;
    return switchStatus_a_btn;
}

