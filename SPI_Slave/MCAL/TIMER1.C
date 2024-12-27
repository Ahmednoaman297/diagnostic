/*
 * TIMER1.c
 *
 *      ModuleName: Timer1
 *      Author: Ahmed Mohamed
 *      Purpose: Source file for Timer1 Driver
 */

/************************************************Includes*********************************************/
#include "TIMER1.h"
/**************************************Global and Static variables***************************************/
uint8_t TIMER1_delayFlag = 0;



/************************************Interrupt Service Routine****************************************/
/***************************************************************
Function Name   : Timer1_intHandler
Inputs          : None
Outputs         : None
Reentrancy      : Non-reentrant
Synchronous     : Synchronous
Description     : Handles the Timer1 interrupt. Clears the interrupt flag and sets
                  the global flag g_delayFlag to indicate the timer delay has completed.
 ****************************************************************/
void TIMER1_intHandler(void)
{
    // Clear the Timer1 interrupt flag to acknowledge the interrupt
    // This ensures that the interrupt handler is ready for the next timeout event
    TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);

    // Set the Timer1_delayFlag flag to true
    TIMER1_delayFlag = 1;
}





/*************************************************functions Definitions*******************************/
/***************************************************************
 Function Name   : TIMER1_delayMsecInterrupt
 Inputs          : uint32_t a_delayInMsec
 Outputs         : void
 Reentrancy      : reentrant
 Synchronous     : Synchronous
 Description     : Configures timer1 as periodic 32 bit timer with interrupt
 ****************************************************************/

void TIMER1_delayMsecInterrupt(uint32_t a_delayInMsec)
{
    /* clear TIMER1_delayFlag */
    TIMER1_delayFlag = false;
    /*Enable Peripheral to TIMER1*/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
    /*wait until Peripheral is Ready */
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER1)) {}
    /* disable  timer */
    TimerDisable(TIMER1_BASE,TIMER_A);
    /*  PERIODIC mode */
    TimerConfigure(TIMER1_BASE, TIMER_CFG_A_PERIODIC);
    /* calculate reload value */
    uint32_t delayCycles = (SysCtlClockGet() / 1000) * a_delayInMsec; //no of cycles =f*no of sec
    /* set reload value */
    TimerLoadSet(TIMER1_BASE, TIMER_A, delayCycles - 1);
    /* put timer1 in startup code*/
    TimerIntRegister(TIMER1_BASE, TIMER_A, TIMER1_intHandler);
    /* enable timer1 with interrupt*/
    TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
    IntEnable(INT_TIMER1A);
    /*enable global interrupt */
    IntMasterEnable();





}

/***************************************************************
 Function Name   : TIMER1_clear
 Inputs          : uint32_t a_delayInMsec
 Outputs         : void
 Reentrancy      : reentrant
 Synchronous     : Synchronous
 Description     : Clears timer1 interrupt flag and disable timer1 then reseting the
                   reload value
 ****************************************************************/
void TIMER1_clear(uint32_t a_delayInMsec)
{

    TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
    TimerDisable(TIMER1_BASE, TIMER_A);
    uint32_t delayCycles = (SysCtlClockGet() / 1000) * a_delayInMsec; /*no of cycles =f*no of sec*/
    /* set reload value */
    TimerLoadSet(TIMER1_BASE, TIMER_A, delayCycles - 1);
    TIMER1_delayFlag =0;
}

/***************************************************************
 Function Name   : TIMER1_start
 Inputs          : void
 Outputs         : void
 Reentrancy      : reentrant
 Synchronous     : ASynchronous
 Description     : timer1 starts counting then fires the interrupt
 ****************************************************************/
void TIMER1_start(void)
{

    TimerEnable(TIMER1_BASE, TIMER_A);
    TIMER1_delayFlag =0;
}
