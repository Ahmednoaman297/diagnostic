/*
 * STATEMACHINE.c
 *
 ModuleName: STATEMACHINE
 Author:     Ahmed Mohamed
 Purpose:    Source file for STATEMACHINE Driver
 */

/*************************************************************Includes**************************************************************/

#include"STATEMACHINE.h"


/********************************************functions Definitions*********************************/

/***************************************************************
Function Name   : CounterClockwise
Inputs          : void
Outputs         : void
Reentrancy      : Reentrancy
Synchronous     : ASynchronous
Description     : Make the leds rotate in Counter clockwise with a given order
 ****************************************************************/

void CounterClockwise (void){
    /*If the white led*/
    if(   GPIOPinRead(GPIO_PORTF_BASE, GREEN_LED)>>3  && (GPIOPinRead(GPIO_PORTF_BASE, RED_LED))>>1 && (GPIOPinRead(GPIO_PORTF_BASE, BLUE_LED))>>2)//cw PB
    {
        /*Clear timer*/
        TIMER1_clear(10000);
        /*Turn on Blue led*/
        LED_blueLight();
        /*Start timer*/
        TIMER1_start();
        /*Delay 1 sec to prevent switching before 1 sec*/
        TIMER0_delayMsec(1000);
    }
    /*if no led is on (when the connection is reconnected)*/
    else if(   !(GPIOPinRead(GPIO_PORTF_BASE, GREEN_LED)>>3)  && !(GPIOPinRead(GPIO_PORTF_BASE, RED_LED)>>1) && !(GPIOPinRead(GPIO_PORTF_BASE, BLUE_LED)>>2))//cw PB
    {
        /*Clear timer*/
        TIMER1_clear(10000);
        /*Turn on Blue led*/
        LED_blueLight();
        /*Start timer*/
        TIMER1_start();
        /*Delay 1 sec to prevent switching before 1 sec*/
        TIMER0_delayMsec(1000);
    }
    /*if the red is on*/
    else if(   !(GPIOPinRead(GPIO_PORTF_BASE, GREEN_LED)>>3)  && (GPIOPinRead(GPIO_PORTF_BASE, RED_LED))>>1 && !(GPIOPinRead(GPIO_PORTF_BASE, BLUE_LED)>>2))//cw PB
    {
        /*Clear timer*/
        TIMER1_clear(10000);
        /*Turn on Blue led*/
        LED_blueLight();
        /*Start timer*/
        TIMER1_start();
        /*Delay 1 sec to prevent switching before 1 sec*/
        TIMER0_delayMsec(1000);
    }
    /*if the Green is on*/
    else if(GPIOPinRead(GPIO_PORTF_BASE, GREEN_LED)>>3 && !(GPIOPinRead(GPIO_PORTF_BASE, RED_LED)>>1) &&!(GPIOPinRead(GPIO_PORTF_BASE, BLUE_LED)>>2))
    {
        /*Clear timer*/
        TIMER1_clear(10000);
        /*Turn on red led*/
        LED_redLight();
        /*Start timer*/
        TIMER1_start();
        /*Delay 1 sec to prevent switching before 1 sec*/
        TIMER0_delayMsec(1000);
    }
    /*if the Blue is on*/
    else if((GPIOPinRead(GPIO_PORTF_BASE, BLUE_LED))>>2 && !(GPIOPinRead(GPIO_PORTF_BASE, GREEN_LED)>>3) && !(GPIOPinRead(GPIO_PORTF_BASE, RED_LED)>>1))
    {
        /*Clear timer*/
        TIMER1_clear(10000);
        /*Turn on Green led*/
        LED_greenLight();
        /*Start timer*/
        TIMER1_start();
        /*Delay 1 sec to prevent switching before 1 sec*/
        TIMER0_delayMsec(1000);
    }
}



/***************************************************************
Function Name   : Clockwise
Inputs          : void
Outputs         : void
Reentrancy      : Reentrancy
Synchronous     : ASynchronous
Description     : Make the leds rotate in clockwise
 ****************************************************************/

void Clockwise (void){
    /*If the white led*/
    if( GPIOPinRead(GPIO_PORTF_BASE, GREEN_LED)>>3  && (GPIOPinRead(GPIO_PORTF_BASE, RED_LED))>>1 && (GPIOPinRead(GPIO_PORTF_BASE, BLUE_LED))>>2  )//cw PB
    {
        /*Clear timer*/
        TIMER1_clear(10000);
        /*Turn on red led*/
        LED_redLight();
        /*Start timer*/
        TIMER1_start();
        /*Delay 1 sec to prevent switching before 1 sec*/
        TIMER0_delayMsec(1000);
    }
    /*if no led is on (when the connection is reconnected)*/
    else if(   !(GPIOPinRead(GPIO_PORTF_BASE, GREEN_LED)>>3)  && !(GPIOPinRead(GPIO_PORTF_BASE, RED_LED)>>1) && !(GPIOPinRead(GPIO_PORTF_BASE, BLUE_LED)>>2))//cw PB
    {
        /*Clear timer*/
        TIMER1_clear(10000);
        /*Turn on red led*/
        LED_redLight();
        /*Start timer*/
        TIMER1_start();
        /*Delay 1 sec to prevent switching before 1 sec*/
        TIMER0_delayMsec(1000);
    }
    /*if the Blue is on*/
    else if( !(GPIOPinRead(GPIO_PORTF_BASE, GREEN_LED)>>3)  && !(GPIOPinRead(GPIO_PORTF_BASE, RED_LED)>>1) && (GPIOPinRead(GPIO_PORTF_BASE, BLUE_LED))>>2 )//cw PB
    {
        /*Clear timer*/
        TIMER1_clear(10000);
        /*Turn on red led*/
        LED_redLight();
        /*Start timer*/
        TIMER1_start();
        /*Delay 1 sec to prevent switching before 1 sec*/
        TIMER0_delayMsec(1000);
    }
    /*if the RED is on*/
    else if( (GPIOPinRead(GPIO_PORTF_BASE, RED_LED))>>1 && !((GPIOPinRead(GPIO_PORTF_BASE, GREEN_LED))>>3) && !((GPIOPinRead(GPIO_PORTF_BASE, BLUE_LED))>>2))
    {
        /*Clear timer*/
        TIMER1_clear(10000);
        /*Turn on Green led*/
        LED_greenLight();
        /*Start timer*/
        TIMER1_start();
        /*Delay 1 sec to prevent switching before 1 sec*/
        TIMER0_delayMsec(1000);
    }
    /*if the Green is on*/
    else if((GPIOPinRead(GPIO_PORTF_BASE, GREEN_LED))>>3 && !((GPIOPinRead(GPIO_PORTF_BASE, RED_LED))>>1) && !((GPIOPinRead(GPIO_PORTF_BASE, BLUE_LED))>>2))
    {
        /*Clear timer*/
        TIMER1_clear(10000);
        /*Turn on Blue led*/
        LED_blueLight();
        /*Start timer*/
        TIMER1_start();
        /*Delay 1 sec to prevent switching before 1 sec*/
        TIMER0_delayMsec(1000);
    }
}



/***************************************************************
Function Name   : Initial_State
Inputs          : void
Outputs         : void
Reentrancy      : Reentrancy
Synchronous     : ASynchronous
Description     : Go to Initial state
 ****************************************************************/

void Initial_State (void){
    /*Clear timer*/
    TIMER1_clear(10000);
    /*Turn on red led*/
    LED_redLight();
    /*Start timer*/
    TIMER1_start();
    /*Delay 1 sec to prevent switching before 1 sec*/
    TIMER0_delayMsec(1000);

}


/***************************************************************
Function Name   : idle_state
Inputs          : void
Outputs         : void
Reentrancy      : Reentrancy
Synchronous     : Synchronous
Description     : Go to idle state
 ****************************************************************/

void idle_state(void)
{
    /*Enter only when the timer1 fires the flag*/
    if (TIMER1_delayFlag == 1)
    {
        /*Turn on White led*/
        LED_whiteLight();
        /*Lowering the 10 sec flag*/
        TIMER1_delayFlag = 0;
        /*Disable timer1 and clear*/
        TIMER1_clear(10000);
        /*Send idle state*/
        SYSTICK_currentState = IDLE;
    }
}

