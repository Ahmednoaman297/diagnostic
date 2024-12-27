/*
 * SYSTICK.c
 *
 *      ModuleName: SYSTICK
 *      Author: Ahmed Mohamed
 *      Purpose: Source file for SYSTICK Driver
 */

/***************************************************Includes***********************************************/

#include "SYSTICK.h"

/*******************************************************Global and Static Variables**********************************************************/
uint8_t  SYSTICK_flag=0;
uint32_t SYSTICK_Sent_data=0;
uint32_t SYSTICK_Get_data=0;


/*******************************************************Interrupt Service Routine**********************************************************/

/***************************************************************
Function Name   : SysTick_Handler
Inputs          : void
Outputs         : void
Reentrancy      : Non-reentrant
Synchronous     : Synchronous
Description     : Handles the Systick interrupt.sets the global flag SYSTICK_Flag
                  to indicate the timer delay has completed.
 ****************************************************************/
void SysTick_Handler(void) {

    /* send data from master to slave using spi */
    SPI_sendData(SYSTICK_Sent_data);
    /*read data sent to slave */
    SSIDataGet(SSI0_BASE, &SYSTICK_Get_data);
    /*Send 4 to make sure that it will make only one change in leds until the next press*/
    SYSTICK_Sent_data = 4;
    /*indicates that systick timer finish counting */
    SYSTICK_flag=1;


}



/**********************************Function Defintions********************************************/

/********************************************************************
    Function Name   : SysTick_Init
    Inputs          : uint32_t a_msec
    Outputs         : void
    Reentrancy      : Non-Reentrant
    Synchronous     : ASynchronous
    Description     : Init the systick timer to fire every 1 sec
 *******************************************************************/
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
}





