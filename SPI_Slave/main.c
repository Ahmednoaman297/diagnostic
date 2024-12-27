/*
 * main.c
 *
 *      ModuleName: main
 *      Author: Ahmed Mohamed
 *      Purpose: main for Slave
 */
/********************************************Includes********************************************/
#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"

#include "driverlib/timer.h"

#include "HAL/LED.h"
#include "HAL/BTN.h"
#include "HAL/STATEMACHINE.h"

#include "MCAL/SYSTICK.h"
#include "MCAL/SPI.h"
#include "MCAL/Timer0.h"


/******************************************Definitions and Macros*********************************/
#define LOST_CONNECTION_PIN   GPIO_PIN_6


/***************************************Functions Definitions***************************************/
/***************************************************************
Function Name   : main_schaduler
Inputs          : uint32_t data
Outputs         : void
Reentrancy      : Reentrancy
Synchronous     : ASynchronous
Description     : Decide which state to execute
 ****************************************************************/
void main_schaduler(uint32_t a_data)
{

    switch(a_data)
    {
    case CW:
        /*To save the number of pressing on CW button*/
        if(SPI_countercw>0)
        {
            SPI_countercw--;
        }
        Clockwise();
        break;
    case CCW:
        /*To save the number of pressing on CCW button*/
        if(SPI_counterccw>0)
        {
            SPI_counterccw--;
        }
        CounterClockwise();

        break;
    case INTIAL_STATE:
        /*To save the number of pressing on button*/
        if(SPI_counterinitial>0)
        {
            SPI_counterinitial--;
        }
        Initial_State();
        break;
    case 4:
        idle_state();
        /*To send idle state to the master for sending on the pc*/
        if( GPIOPinRead(GPIO_PORTF_BASE, GREEN_LED)>>3  && (GPIOPinRead(GPIO_PORTF_BASE, RED_LED))>>1 && (GPIOPinRead(GPIO_PORTF_BASE, BLUE_LED))>>2  )//cw PB
        {SYSTICK_currentState = IDLE;}
        break;
    default:
        /* Unidentified state*/
        SYSTICK_currentState = ERROR_STATE;
        /* Error: unidentified state*/
        break;
    }

}

/***************************************************************
Function Name   : main_initialization
Inputs          : void
Outputs         : void
Reentrancy      : Reentrancy
Synchronous     : Synchronous
Description     : Initialize all modules and peripherals
 ****************************************************************/
void main_initialization (void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA));
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, LOST_CONNECTION_PIN );
    GPIOPinWrite(GPIO_PORTA_BASE, LOST_CONNECTION_PIN, 0);
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, SYSTICK_ERROR_PIN );
    GPIOPinWrite(GPIO_PORTA_BASE, SYSTICK_ERROR_PIN, 0);

    /*Initialize SPI as slave*/
    SPI_init(SLAVE);
    /*Initialize the systick to fire every 10ms*/
    SYSTICK_delayMSec(10);


    /*Initialize LED*/
    LED_config();
    LED_whiteLight();

    TIMER1_delayMsecInterrupt(10000);
    /*Initialize the lost connection pin to send the error*/

}



/*******************************************Main***********************************************/
int main(void) {
    /*Call the initialization function for all modules*/
    main_initialization();
    while (1)
    {
        /*Check that the connection is lost*/
        if (SPI_lostconnectionflag)
        {
            /*Put high on the pin to indicate that the connection is lost*/
            GPIOPinWrite(GPIO_PORTA_BASE, LOST_CONNECTION_PIN, LOST_CONNECTION_PIN);
            /*Turn the leds off*/
            LEDS_off();
            /*Reset all the variable to be ready if the connection is back*/
            SYSTICK_currentState = 0;
            SPI_countercw=0;
            SPI_counterccw=0;
            SPI_counterinitial=0;
            SYSTICK_data =4;
        }
        /*Go on with the code if the slave is connected with the master*/
        else
        {
            /*Put low on the pin to indicate that the connection is good*/
            GPIOPinWrite(GPIO_PORTA_BASE, LOST_CONNECTION_PIN, 0);

            /*Lowering the systick flag*/
            SYSTICK_isr_flag = 0;
            /*Call the scheduler*/
            /*The next condition to save the number of pressing
             * the button because of  (1 second delay)*/
            if(SPI_countercw>0)
            {
                main_schaduler(CW);
            }
            else if(SPI_counterccw>0)
            {
                main_schaduler(CCW);
            }
            else if(SPI_counterinitial>0)
            {
                main_schaduler(INTIAL_STATE);
            }
            else
            {
                main_schaduler(SYSTICK_data);
            }

        }

    }
}

