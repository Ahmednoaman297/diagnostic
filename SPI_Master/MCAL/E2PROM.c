/*
 * E2PROM.c
 *
 *  Created on: Dec 14, 2024
 *      Author: elder
 */
#include "E2PROM.h"
#define EEPROM_PAGE_SIZE 16  // Typically, Tiva C EEPROM has 16-byte blocks

void InitEEPROM(void)
{
    // Enable the EEPROM module
    SysCtlPeripheralEnable(SYSCTL_PERIPH_EEPROM0);

    // Wait for the EEPROM module to be ready
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_EEPROM0))
    {
    }

    // Initialize the EEPROM
    EEPROMInit();
}
void WriteToEEPROM(uint32_t address, uint32_t data)
{


    // Write data to the specified EEPROM address
    EEPROMProgram(&data, address, sizeof(data));
}
uint32_t ReadFromEEPROM(uint32_t address)
{
    uint32_t data;



    // Read data from the specified EEPROM address
    EEPROMRead(&data, address, sizeof(data));

    return data;
}

void ClearEEPROM(uint32_t startAddress, uint32_t endAddress) {
    // Initialize EEPROM
    if (EEPROMInit() != EEPROM_INIT_OK) {
        // Handle initialization error (e.g., EEPROM not configured)
        return;
    }

    // Loop through the EEPROM memory range
    uint32_t address;
    for ( address= startAddress; address <= endAddress; address += EEPROM_PAGE_SIZE) {
        uint32_t emptyData[EEPROM_PAGE_SIZE / 4] = {0xFFFFFFFF}; // Data to clear a page (16 bytes = 4 words)

        // Erase (write all 0xFFFFFFFF to clear)
        EEPROMProgram(emptyData, address, EEPROM_PAGE_SIZE);

        // Wait until the operation completes
        while (EEPROMStatusGet() != 0) {
            SysCtlDelay(1000); // Small delay
        }
    }
}

