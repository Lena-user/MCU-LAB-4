/*
 * Scheduler.h
 *
 *  Created on: Dec 2, 2024
 *      Author: dangk
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "stdint.h"


#define SCH_MAX_TASKS 			40
#define TICK					10
typedef struct {
	void ( * pTask)(void);
	uint32_t Delay;
	uint32_t Period;
	uint8_t RunMe;
	uint32_t TaskID;
} sTask;

void SCH_Init(void);
void SCH_Update(void);
uint8_t SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD);
void SCH_Dispatch_Tasks(void);
void SCH_Delete_Task(uint8_t TASK_ID);

#endif /* INC_SCHEDULER_H_ */
