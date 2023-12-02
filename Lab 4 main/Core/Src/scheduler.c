/*
 * scheduler.c
 *
 *  Created on: Nov 30, 2023
 *      Author: DELL F89F
 */

#include "scheduler.h"

sNodes SCH_tasks_G[SCH_MAX_TASKS];
uint8_t current_idx_task = 0;
const int TICK = 10;

void SCH_INIT(void){
	current_idx_task = 0;
	for (int i = 0; i < SCH_MAX_TASKS; i++){
		SCH_tasks_G[i].check = 0;
		SCH_tasks_G[i].ID = i;
	}
}

void SCH_Add_Task(void (*pFunction)(), uint32_t Delay, uint32_t Period){
	if (current_idx_task < SCH_MAX_TASKS){
		for (int i = 0; i <= current_idx_task; i++){
			if (SCH_tasks_G[i].check == 0){
				SCH_tasks_G[i].data.pTask = pFunction;
				SCH_tasks_G[i].data.Delay = Delay/TICK;
				SCH_tasks_G[i].data.Period = Period/TICK;
				SCH_tasks_G[i].data.RunMe = 0;

				SCH_tasks_G[i].data.TaskID = SCH_tasks_G[i].ID;
				SCH_tasks_G[i].check = 1;
				current_idx_task++;
				break;
			}
		}
	}
}

void SCH_Update(void){
	for (int i = 0; i < current_idx_task; i++){
		if (SCH_tasks_G[i].check == 1){
			if (SCH_tasks_G[i].data.Delay > 0){
				SCH_tasks_G[i].data.Delay--;
			}
			else{
				SCH_tasks_G[i].data.Delay = SCH_tasks_G[i].data.Period;
				SCH_tasks_G[i].data.RunMe++;
			}
		}
	}
}

void SCH_Delete_Task(uint8_t index){
	if (SCH_tasks_G[index].check == 1){
		SCH_tasks_G[index].check = 0;
	}
}

void SCH_Dispatch_Task(void){
	for (int i = 0; i < current_idx_task; i++){
		if (SCH_tasks_G[i].check == 1){
			if (SCH_tasks_G[i].data.RunMe > 0){
				SCH_tasks_G[i].data.RunMe--;
				(*SCH_tasks_G[i].data.pTask)(); // do work

				if (SCH_tasks_G[i].data.Period == 0){
					SCH_Delete_Task(i);
				}
			}
		}
	}
}
