/*
 * SPI.c
 *
 *      ModuleName: SPI
 *      Author: Ahmed Mohamed
 *      Purpose: Source file for SPI Driver
 */

/**************************************************************Includes*********************************************************************/
#include "SPI.h"

/*******************************************************Functions Definitions**********************************************************/

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
Reentrancy      : Non-Reentrant
Synchronous     : Synchronous
Description     : Used to send data from master to slave
****************************************************************/



void SPI_sendData(uint32_t a_data)
{
    SSIDataPut(SSI0_BASE, a_data);

    while(SSIBusy(SSI0_BASE))
    {}

}



/***************************************************************
Function Name   : SPI_receiveData
Inputs          : Void
Outputs         : uint32_t receivedData
Reentrancy      : Reentrant
Synchronous     : Synchronous
Description     : Used to receive the data sent from master
****************************************************************/

uint32_t SPI_receiveData(void)
{
    uint32_t receivedData;
    /* Wait until data is available in the receive FIFO*/
    while (SSIDataGetNonBlocking(SSI0_BASE, &receivedData) == false) { }
    return receivedData;

}




