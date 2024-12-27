/*
 * Monitor.h
 *
 *  Created on: Dec 14, 2024
 *      Author: elder
 */

#ifndef SERVICE_MONITOR_H_
#define SERVICE_MONITOR_H_
#include "../MCAL/E2PROM.h"
#include "Nvm.h"
extern uint8_t Fault_flag;
extern uint8_t maintenance;
void Check_flag(void);

#endif /* SERVICE_MONITOR_H_ */
