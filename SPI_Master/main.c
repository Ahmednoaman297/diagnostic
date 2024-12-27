/*
 *      ModuleName: main
 *      Author: Ahmed Mohamed
 *      Purpose: main for Master
 */


/********************************************Includes*********************************/
#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"

#include "utils/uartstdio.h"

#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/uart.h"

#include "driverlib/pin_map.h"
#include "driverlib/ssi.h"


#include "MCAL/SPI.h"
#include "MCAL/SYSTICK.h"
#include "MCAL/UARTs/UARTS.h"
#include "MCAL/Timer0.h"

#include "HAL/LED.h"
#include "HAL/BTN.h"
#include "MCAL/E2PROM.h"
#include "Service/Monitor.h"
#include "Service/Nvm.h"

/********************************************Definitions and Macros*********************************/

#define FIRST_SWITCH          GPIO_PIN_0      /* Indicates the first button which sends the first state*/
#define SECOND_SWITCH         GPIO_PIN_4      /* Indicates the Second button which sends the Second state*/
#define LOST_CONNECTION_PIN   GPIO_PIN_6
#define SYSTICK_ERROR_PIN     GPIO_PIN_7
#define PRESSED                  0            /* Indicates the button is pressed active low*/
#define NOT_PRESSED              1
#define CW                       1            /* Macros for the states*/
#define CCW                      2
#define INITIAL_STATE            3
#define ERROR_STATE             0x09           /* Error in sending the data to the slave*/
#define IDLE                    0x06           /* The slave enters the idle state*/
#define ERROR_INPUTLED          0x12
#define ERROR_GPIO              0x13
#define ERROR_SYSTICK           0x11

/********************************************Global and Static variables*********************************/
uint8_t flag=0;
uint8_t switch1 =0;
uint8_t switch2 = 0;

/********************************************Functions Definitions*********************************/
void recover(void);

/***************************************************************
Function Name   : main_initialization
Inputs          : void
Outputs         : void
Reentrancy      : Non-Reentrancy
Synchronous     : Synchronous
Description     : Initialize all modules and peripherals
 ****************************************************************/

void main_initialization (void)
{
    /* Set the system clock to 50 MHz*/
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    /*initialize Systick fires every 50 ms*/
    SYSTICK_delayMSec(50);
    /*initialize spi*/
    SPI_init(MASTER);
    /*initialize the lost connection pin as input*/
    GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, LOST_CONNECTION_PIN );
    GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, SYSTICK_ERROR_PIN );
    /*initialize uart*/

    BTN_init();
    /*initialize buttons on tiva*/
    LED_config();
    InitEEPROM();
    /*initialize leds on tiva*/
}

/********************************************Main*********************************/
int main(void)
{
    /*Function to initialize all the modules*/
    main_initialization();
    /*Variable to read the state of the switches*/







    while (1)
    {
        /*Read the lost connection pin to make sure the connection is not lost*/
        uint8_t lostconn = BTN_read(LOST_CONNECTION_PIN,GPIO_PORTA_BASE);
        uint8_t systick_error = BTN_read(SYSTICK_ERROR_PIN,GPIO_PORTA_BASE);

        /*Blinking Red LED if the Connection is lost with the slave*/
        if ( lostconn == 1)
        {
            LED_redLight();
            TIMER0_delayMsec(500);
            LEDS_off();
            TIMER0_delayMsec(500);
            /*Sending to the screen communication lost*/
            UART_sendString("Communication Lost\r\n",0);

            Check_flag();
            if(maintenance==0)
            {
                UART_sendString("Maintenance_LED_ON\r\n",0);
            }
        }
        else if(lostconn==0 && maintenance==0)
        {
            ClearEEPROM(0x000000, 0x000FFF);
            Fault_flag=0;
            LEDS_off();
            maintenance=1;
            UART_sendString("Maintenance_LED_OFF\r\n",0);

        }
        else if(systick_error == 1)
        {
            TIMER0_delayMsec(1000);
            /*Send Error for systick enable*/
            UART_sendString("ECU2: Error in SYSTICK\r\n",0);
            /*make the variable equal zero to check if the error still occurs or not*/
            SYSTICK_Get_data=0;
        }
        /*Go on with the code if there is connection with the slave*/
        else
        {
            /*Reading both switches*/
            switch1= BTN_read(FIRST_SWITCH,GPIO_PORTF_BASE) ;
            switch2= BTN_read(SECOND_SWITCH,GPIO_PORTF_BASE) ;

            /*debouncing for both switches*/
            if(PRESSED ==switch1 || PRESSED ==switch2)
            {
                /*debouncing by timer0 100 ms*/
                TIMER0_delayMsec(200);

                /*Reading both switches after the debouncing*/
                switch1= BTN_read(FIRST_SWITCH,GPIO_PORTF_BASE) ;
                switch2= BTN_read(SECOND_SWITCH,GPIO_PORTF_BASE) ;

                /*Clockwise state condition*/
                if(PRESSED ==switch1 && PRESSED !=switch2)
                {
                    /*Just visual indicator that the button is working*/
                    LED_blueLight();

                    /*this flag indicates that systick timer complete 50ms*/
                    if(1==SYSTICK_flag)
                    {
                        /*Updating the data after 50 ms with CW*/
                        SYSTICK_Sent_data=CW;

                        /*Lowering the Systick flag*/
                        SYSTICK_flag=0;
                    }

                    UART_sendString("Machine State is ClockWise\r\n",0);
                    /*variable to indicate that there is no error in data sending*/
                    SYSTICK_Get_data=0;
                }

                /*Counter-Clockwise state condition*/
                else if(PRESSED ==switch2 && PRESSED !=switch1)
                {
                    /*Just visual indicator that the button is working*/
                    LED_redLight();
                    /*this flag indicates that systick timer complete 50ms*/
                    if(1==SYSTICK_flag)
                    {
                        /*Updating the data after 50 ms with CCW*/
                        SYSTICK_Sent_data=CCW;

                        /*Lowering the Systick flag*/
                        SYSTICK_flag=0;
                    }
                    UART_sendString("Machine State is Counter ClockWise\r\n",0);
                    /*variable to indicate that there is no error in data sending*/
                    SYSTICK_Get_data=0;


                }

                /*Intial state condition*/
                else if(PRESSED == switch1 && PRESSED == switch2)
                {
                    /*Just visual indicator that the button is working*/
                    LED_greenLight();
                    /*this flag indicates that systick timer complete 50ms*/
                    if(1==SYSTICK_flag)
                    {
                        /*Updating the data after 50 ms with CCW*/
                        SYSTICK_Sent_data=INITIAL_STATE;

                        /*Lowering the Systick flag*/
                        SYSTICK_flag=0;
                    }
                    UART_sendString("Machine State is Initial State\r\n",0);
                    /*variable to indicate that there is no error in data sending*/
                    SYSTICK_Get_data=0;

                }
            }

            /*If there is no switch is pressed check on the data error*/
            else
            {
                /*The data received by the slave is incorrect*/
                if(ERROR_STATE==SYSTICK_Get_data)
                {
                    TIMER0_delayMsec(1000);
                    /*Send Error unidentified state received to the screen*/
                    UART_sendString("ECU2: Error unidentified state received\r\n",0);
                    /*make the variable equal zero to check if the error still occurs or not*/
                    SYSTICK_Get_data=0;
                }
                /*The slave is in idle state*/
                else if(IDLE==SYSTICK_Get_data)
                {
                    /*Delay 1 second*/
                    TIMER0_delayMsec(1000);
                    /*Send Machine State is Idle State to the screen*/
                    UART_sendString("Machine State is Idle State\r\n",0);
                    /*make the variable equal zero to check if the slave still in idle state or not*/
                    SYSTICK_Get_data=0;
                }
                /*error in the gpio module clock on the slave ecu*/
                else if(ERROR_GPIO==SYSTICK_Get_data)
                {
                    /*Delay 1 second*/
                    TIMER0_delayMsec(1000);
                    /*Send Error to the computer because oo GPIO*/
                    UART_sendString("ECU2: Error in GPIO enable\r\n",0);
                    /*make the variable equal zero to check if the slave still in idle state or not*/
                    SYSTICK_Get_data=0;
                }
                else if(ERROR_INPUTLED==SYSTICK_Get_data)
                {
                    /*Delay 1 second*/
                    TIMER0_delayMsec(1000);
                    /*Send to the screen error because of initializing the leds on the slave ecu*/
                    UART_sendString("ECU2: Error in LEDS initialization \r\n",0);
                    /*make the variable equal zero to check if the slave still in idle state or not*/
                    SYSTICK_Get_data=0;
                }



            }

        }

    }

}

