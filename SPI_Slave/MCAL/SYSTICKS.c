/*
 * SYSTICK.c
 *
 *      ModuleName: SYSTICK
 *      Author: Ahmed Mohamed
 *      Purpose: Source file for SYSTICK Driver
 */

/***************************************************Includes***********************************************/
#include "SYSTICK.h"

/***************************************Global Variables*****************************************/
uint32_t SYSTICK_data =0;
uint8_t SYSTICK_flag=0;
uint8_t SYSTICK_isr_flag=0;
uint32_t SYSTICK_currentState=0;
uint8_t SYSTICK_flagConnection = 0;


/************************************Interrupt Service Routine********************************/

/***************************************************************
Function Name   : SysTick_Handler
Inputs          : void
Outputs         : void
Reentrancy      : Non-reentrant
Synchronous     : Synchronous
Description     : Handles the Systick interrupt.sets the global flag SYSTICK_Flag
                  to indicate the timer delay has completed.
 ****************************************************************/

void SysTick_Handler(void)
{
    /* data received from Master*/
    SYSTICK_data=SPI_receiveData();
    /* Put data get from Master */
    /*this flag used to send current state of slave to master*/
    SYSTICK_currentState=0;
    SYSTICK_isr_flag =1;



}

/*******************************************************Functions Definitions**********************************************************/

/***************************************************************
Function Name   : SysTick_Init
Inputs          : uint32_t a_msec
Outputs         : void
Reentrancy      : Reentrant
Synchronous     : Synchronous
Description     : Initialize the systick timer to fire every X msec
 ****************************************************************/
void SYSTICK_delayMSec(uint32_t a_msec)
{
    /* Calculate the reload value // (  Desired Frequency/System Clock Frequency )-1*/
    uint32_t reloadValue = ((SysCtlClockGet() / 1000) * a_msec)-1;
    /*set reloadValue in NVIC_ST_RELOAD REG */
    SysTickPeriodSet(reloadValue -1);
    /*updates the vector table to point to  SysTick_Handler function. */
    SysTickIntRegister(SysTick_Handler);
    /* Enable SysTick with interrupt */
    SysTickIntEnable();

    /* Enable Systick*/
    SysTickEnable();
    /* Enable global interrupt */
    IntMasterEnable();
    /*Check if there is any error in enabling the systick*/
    if (!(HWREG(NVIC_ST_CTRL) & NVIC_ST_CTRL_ENABLE)) {
        /* SysTick not enabled*/
        while (1) {
            SYSTICK_currentState = ERROR_SYSTICK;
            GPIOPinWrite(GPIO_PORTA_BASE, SYSTICK_ERROR_PIN, SYSTICK_ERROR_PIN);
        }
    }
}
