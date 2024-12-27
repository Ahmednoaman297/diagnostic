/*
 * E2PROM.h
 *
 *  Created on: Dec 14, 2024
 *      Author: elder
 */

#ifndef E2PROM_H_
#define E2PROM_H_
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_eeprom.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/eeprom.h"
#include "driverlib/pin_map.h"
#include "utils/uartstdio.h"

void InitEEPROM(void);
void WriteToEEPROM(uint32_t address, uint32_t data);
uint32_t ReadFromEEPROM(uint32_t address);
void ClearEEPROM(uint32_t startAddress, uint32_t endAddress) ;





#endif /* E2PROM_H_ */
