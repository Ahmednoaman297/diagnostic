/*
 * Nvm.c
 *
 *  Created on: Dec 14, 2024
 *      Author: elder
 */
#include "Nvm.h"
void Read_Fault(void)
{

    Fault_flag++;
    WriteToEEPROM(0x000000,Fault_flag);
}


