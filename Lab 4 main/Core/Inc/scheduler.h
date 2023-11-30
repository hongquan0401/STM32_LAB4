/*
 * scheduler.h
 *
 *  Created on: Nov 30, 2023
 *      Author: DELL F89F
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "stdint.h"

#define SCH_MAX_TASKS 10

typedef struct{
	void (*pTask)(void);
	uint32_t Delay;
	uint32_t Period;
	uint8_t RunMe;

	uint32_t TaskID;
}sTasks;

void SCH_INIT(void);

void SCH_Add_Task(void (*pFunction)(), uint32_t Delay, uint32_t Period);

void SCH_Update(void);

void SCH_Dispatch_Task(void);

#endif /* INC_SCHEDULER_H_ */
