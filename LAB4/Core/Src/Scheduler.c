/*
 * Scheduler.c
 *
 *  Created on: Dec 2, 2024
 *      Author: dangk
 */

#include "scheduler.h"

static sTask SCH_tasks_G[SCH_MAX_TASKS];

void SCH_Init(void){
	for(int i = 0; i < SCH_MAX_TASKS; i++){
		SCH_tasks_G[i].pTask = 0x0000000;
		SCH_tasks_G[i].Delay = 0;
		SCH_tasks_G[i].Period = 0;
		SCH_tasks_G[i].RunMe = 0;
		SCH_tasks_G[i].TaskID = 0;
	}
}

void SCH_Update(void){
	 for(int i = 0; i < SCH_MAX_TASKS; i++){
		 if(SCH_tasks_G[i].Delay > 0){
			 SCH_tasks_G[i].Delay --;
		 }else{

				 SCH_tasks_G[i].Delay = SCH_tasks_G[i].Period;
				 SCH_tasks_G[i].RunMe += 1;
		 }
	 }
}

uint8_t SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD){
	uint8_t Index = 0;
	while ((SCH_tasks_G[Index].pTask != 0) && (Index < SCH_MAX_TASKS))
		Index++;
	SCH_tasks_G[Index].pTask = pFunction;
	SCH_tasks_G[Index].Delay = DELAY/TICK;
	SCH_tasks_G[Index].Period = PERIOD/TICK;
	SCH_tasks_G[Index].RunMe = 0;
	SCH_tasks_G[Index].TaskID = Index;
	return Index;
}


void SCH_Delete_Task(uint8_t taskID)
{
		SCH_tasks_G[taskID].pTask = 0x0000000;
		SCH_tasks_G[taskID].Period = 0;
		SCH_tasks_G[taskID].Delay = 0;
		SCH_tasks_G[taskID].RunMe = 0;
		SCH_tasks_G[taskID].TaskID = 0;
}

void SCH_Dispatch_Tasks(void){
	 for(int i = 0; i < SCH_MAX_TASKS; i++){
		 if(SCH_tasks_G[i].RunMe > 0){
			 SCH_tasks_G[i].RunMe --;
			 if(SCH_tasks_G[i].pTask){
				 (*SCH_tasks_G[i].pTask)();
			 }
			 if(SCH_tasks_G[i].Period == 0){
				 SCH_Delete_Task(i);
			 }

		 }
	 }
}
