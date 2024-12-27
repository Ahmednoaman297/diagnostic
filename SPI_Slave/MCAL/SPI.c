/*
 * SPI.c
 *
 *      ModuleName: SPI
 *      Author: Ahmed Mohamed
 *      Purpose: Source file for SPI Driver
 */
/**************************************************************Includes*********************************************************************/
#include "SPI.h"


/***************************************Global Variables*****************************************/
uint8_t SPI_lostconnectionflag =0;
uint32_t g_counterspi = 0;
uint32_t SPI_counterccw =0;
uint32_t SPI_countercw =0;
uint32_t SPI_counterinitial =0;

/******************************************Function Definitions****************************************/
/***************************************************************
Function Name   : SPI_init
Inputs          : uint8_t a_mode
Outputs         : void
Reentrancy      : Reentrant
Synchronous     : Synchronous
Description     : Initialize the micro-controller whether Master or Slave
 ****************************************************************/
void SPI_init(uint8_t a_MODE)
{
    /* Step 1: Enable peripherals for SPI (SSI0) and the GPIO port A*/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_SSI0));
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA));

    /* Step 2: Configure GPIO pins for SSI0 (SPI)*/
    GPIOPinConfigure(GPIO_PA2_SSI0CLK);  // PA2 -> SSI0CLK
    GPIOPinConfigure(GPIO_PA3_SSI0FSS);  // PA3 -> SSI0FSS
    GPIOPinConfigure(GPIO_PA4_SSI0RX);   // PA4 -> SSI0RX
    GPIOPinConfigure(GPIO_PA5_SSI0TX);   // PA5 -> SSI0TX

    /* Configure the GPIO Pins for SPI communication*/
    GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5);

    /* Step 3: Configure the SSI0 module for SPI communication*/
    /*MASTER | SLAVE*/
    if ( 0 == a_MODE)
    {
        SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_0,
                           SSI_MODE_SLAVE, 1000000, 8);  // 1 MHz SPI clock, 8-bit data
    }
    else if ( 1== a_MODE)
    {
        SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_0,
                           SSI_MODE_MASTER, 1000000, 8);  // 1 MHz SPI clock, 8-bit data
    }
    /* Step 4: Enable the SSI module*/ //&& interrupt on transmit fifo empty

    SSIEnable(SSI0_BASE);


}

/***************************************************************
Function Name   : SPI_sendData
Inputs          : uint32_t a_data
Outputs         : Void
Reentrancy      : Reentrant
Synchronous     : Synchronous
Description     : Used to send data from master to slave
 ****************************************************************/



void SPI_sendData(uint32_t a_data)
{
    while(SSIBusy(SSI0_BASE))
    {}

    SSIDataPut(SSI0_BASE, a_data);


}



/***************************************************************
Function Name   : SPI_receiveData
Inputs          : Void
Outputs         : uint32_t receivedData
Reentrancy      : Reentrant
Synchronous     : ASynchronous
Description     : Used to receive the data sent from master
 ****************************************************************/

uint32_t SPI_receiveData(void)
{
    uint32_t receivedData;
    /* Wait until data is available in the receive FIFO*/
    if (SSIDataGetNonBlocking(SSI0_BASE, &receivedData) == false) {
        /*Counter to count the number of iterations in systick handler the slave
         * didn't read data from the master indicating that connection is lost*/
        g_counterspi++;
        if(g_counterspi>=200)
        {
            /*Flag to indicate the connection is lost*/
            SPI_lostconnectionflag = 1;
        }
        /*return the previous data to hold the same state*/
        return SYSTICK_data ;
    }
    else
    {
        /*if there is data came from the master put the data to be
        *sent to the master to check for errors*/
        SSIDataPutNonBlocking(SSI0_BASE, SYSTICK_currentState);
        /*resting the counter and the flag indicating that
         * the connection is goodOR reconnected*/
        g_counterspi =0;
        SPI_lostconnectionflag =0;
        /*The next condition is for counting how many times the slave received
         * the same state which indicates that the user pressed the button many
         * times on the master ECU so counter to save how many times each state
         * is pressed acting as counting semaphore*/
        if (receivedData == 2)
        {
            /*counter for CCW BTN*/
            SPI_counterccw++;

        }
        else if(receivedData == 1)

        {
            /*counter for CW BTN*/
            SPI_countercw++;

        }
        else if (receivedData == 3)
        {
            /*counter for Initial state BTN*/
            SPI_counterinitial++;
        }
        /*returning the read data*/
        return receivedData;
    }

}




