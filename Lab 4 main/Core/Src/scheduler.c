/*
 * scheduler.c
 *
 *  Created on: Nov 30, 2023
 *      Author: DELL F89F
 */

#include "scheduler.h"

sTasks SCH_tasks_G[SCH_MAX_TASKS];
uint8_t current_idx_task = 0;

void SCH_INIT(void){
	current_idx_task = 0;
}

void SCH_Add_Task(void (*pFunction)(), uint32_t Delay, uint32_t Period){
	if (current_idx_task < SCH_MAX_TASKS){
		SCH_tasks_G[current_idx_task].pTask = pFunction;
		SCH_tasks_G[current_idx_task].Delay = Delay;
		SCH_tasks_G[current_idx_task].Period = Period;
		SCH_tasks_G[current_idx_task].RunMe = 0;

		SCH_tasks_G[current_idx_task].TaskID = current_idx_task;
	}
}

void SCH_Update(void){
	for (int i = 0; i < current_idx_task; i++){
		if (SCH_tasks_G[i].Delay > 0){
			SCH_tasks_G[i].Delay--;
		}
		else{
			SCH_tasks_G[i].Delay = SCH_tasks_G[i].Period;
			SCH_tasks_G[i].RunMe++;
		}
	}
}

void SCH_Dispatch_Task(void){
	for(int i = 0; i < current_idx_task; i++){
		if(SCH_tasks_G[i].RunMe > 0){
			SCH_tasks_G[i].RunMe--;
			(*SCH_tasks_G[i].pTask)();  //Do work
		}
	}
}
