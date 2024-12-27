/*
 * Timer0.c
 *
 *      ModuleName: Timer0
 *      Author: Ahmed Mohamed
 *      Purpose: Source file for Timer0 Driver
 */


/************************************************Includes*********************************************/
#include "Timer0.h"
/**************************************Global and Static variables***************************************/
uint8_t Timer0_delayFlag = 0;


/************************************Interrupt Service Routine****************************************/
/***************************************************************
Function Name   : Timer0_intHandler
Inputs          : None
Outputs         : None
Reentrancy      : Non-reentrant
Synchronous     : Synchronous
Description     : Handles the Timer0 interrupt. Clears the interrupt flag and sets
                  the global flag g_delayFlag to indicate the timer delay has completed.
 ****************************************************************/
void TIMER0_intHandler(void)
{
    // Clear the Timer0 interrupt flag to acknowledge the interrupt
    // This ensures that the interrupt handler is ready for the next timeout event
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    // Set the Timer0_delayFlag flag to true
    // This indicates to other parts of the program that the timer delay has completed
    Timer0_delayFlag = 1;
}


/*************************************************functions Definitions*******************************/
/***************************************************************
 Function Name   : TIMER0_delayMsec
 Inputs          : uint32_t delayInMs
 Outputs         : None
 Reentrancy      : Non-reentrant
 Synchronous     : Synchronous
 Description     : Configures Timer0 as a one-shot timer to generate a delay for the
                   specified duration in milliseconds. Enables Timer0 interrupts, waits
                   for the timer to complete the delay, and disables interrupts after
                   completion. Uses g_delayFlag to monitor delay status.
 ****************************************************************/

void TIMER0_delayMsec(uint32_t a_delayInMsec)
{
    /* clear Timer0_delayFlag */
    Timer0_delayFlag = false;
    /*Enable Peripheral to timer0*/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    /*wait until Peripheral is Ready */
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0)) {}
    /* disable  timer */
    TimerDisable(TIMER0_BASE,TIMER_A);
    /* one shot mode */
    TimerConfigure(TIMER0_BASE, TIMER_CFG_A_ONE_SHOT);
    /* calculate reload value */
    uint32_t delayCycles = (SysCtlClockGet() / 1000) * a_delayInMsec; //no of cycles =f*no of sec
    /* set reload value */
    TimerLoadSet(TIMER0_BASE, TIMER_A, delayCycles - 1);
    /* put timer0 in startup code*/
    TimerIntRegister(TIMER0_BASE, TIMER_A, TIMER0_intHandler);
    /* enable timer0 with interrupt*/
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    IntEnable(INT_TIMER0A);
    /*enable global interrupt */
    IntMasterEnable();
    TimerEnable(TIMER0_BASE, TIMER_A);
    /* wait until counting finished */
    while (!Timer0_delayFlag) {}



}
