

/*
 * SPI.h
 *
 *      ModuleName: SPI
 *      Author: Ahmedmohamed
 *      Purpose: Header file for SPI Driver
 */

#ifndef SPI_H_
#define SPI_H_

/********************************************Includes*********************************/

#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/ssi.h"
#include "driverlib/interrupt.h"

#include "SYSTICK.h"

/*******************************************************Shared Global Variable(extern)**********************************************************/

extern uint32_t SPI_counterccw ;
extern uint32_t SPI_countercw ;
extern uint32_t SPI_counterinitial ;
extern uint8_t SPI_lostconnectionflag ;

/********************************************Definitions and Macros*********************************/
#define SLAVE 0
#define MASTER 1


/********************************************functions prototypes*********************************/
void SPI_init(uint8_t a_MODE);
void SPI_sendData(uint32_t a_data);
uint32_t SPI_receiveData(void) ;


#endif /* SPI_H_ */
