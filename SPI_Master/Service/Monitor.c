/*
 * Monitor.c
 *
 *  Created on: Dec 14, 2024
 *      Author: elder
 */

#include "Monitor.h"
uint8_t Fault_flag=0;
uint8_t maintenance=1;
void Check_flag(void)
{
    Read_Fault();
   if(ReadFromEEPROM(0x000000)==3)
   {
       maintenance=0;
  }
}


