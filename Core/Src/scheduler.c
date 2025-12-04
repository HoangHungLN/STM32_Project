/*
 * scheduler.c
 *
 *  Created on: Nov 19, 2025
 *      Author: Hoàng Hưng
 */

#ifndef SRC_SCHEDULER_C_
#define SRC_SCHEDULER_C_

#include "scheduler.h"

sTask SCH_tasks_G[SCH_MAX_TASKS];
uint32_t taskID = 0;

void SCH_Init(void) {
    for (int i = 0; i < SCH_MAX_TASKS; i++) {
        SCH_tasks_G[i].pTask = 0;
        SCH_tasks_G[i].Delay = 0;
		SCH_tasks_G[i].Period = 0;
		SCH_tasks_G[i].RunMe = 0;
		SCH_tasks_G[i].TaskID = 0;
    }
}

void SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD){
	uint32_t index_delay = 0;
	uint32_t newDelay = 0;
	uint32_t newID;
	taskID++;
	if (taskID == 0) taskID++;
	newID = taskID;
	for(int i = 0; i < SCH_MAX_TASKS; i++){
		if (SCH_tasks_G[i].pTask == 0) {
			SCH_tasks_G[i].pTask  = pFunction;
			SCH_tasks_G[i].Delay  = DELAY - index_delay;
			SCH_tasks_G[i].Period = PERIOD;
			SCH_tasks_G[i].RunMe  = (SCH_tasks_G[i].Delay == 0) ? 1 : 0;
			SCH_tasks_G[i].TaskID = newID;
			return;
		}

		index_delay += SCH_tasks_G[i].Delay;
		if(DELAY < index_delay){
			newDelay = DELAY - index_delay + SCH_tasks_G[i].Delay;
			SCH_tasks_G[i].Delay = index_delay - DELAY;
			for(int j = SCH_MAX_TASKS - 1; j > i; j--){
				SCH_tasks_G[j] = SCH_tasks_G[j - 1];
			}
			SCH_tasks_G[i].pTask = pFunction;
			SCH_tasks_G[i].Period = PERIOD;
			SCH_tasks_G[i].Delay = newDelay;
			SCH_tasks_G[i].RunMe = (newDelay == 0) ? 1 : 0;
			SCH_tasks_G[i].TaskID = newID;
			return;
		}
	}
}


void SCH_Delete_Task(uint32_t taskID){
	if(taskID == 0) return;
	for(int i = 0; i < SCH_MAX_TASKS; i++) {
		if(SCH_tasks_G[i].TaskID == taskID){
			if(i < SCH_MAX_TASKS - 1 && SCH_tasks_G[i + 1].pTask != 0)
				SCH_tasks_G[i + 1].Delay += SCH_tasks_G[i].Delay;
			int j;
			for(j = i; j < SCH_MAX_TASKS - 1; j++){
				SCH_tasks_G[j] = SCH_tasks_G[j + 1];
			}
			SCH_tasks_G[j].pTask = 0;
			SCH_tasks_G[j].Period = 0;
			SCH_tasks_G[j].Delay = 0;
			SCH_tasks_G[j].RunMe = 0;
			SCH_tasks_G[j].TaskID = 0;
			return;
		}
	}
}

void SCH_Update(void) {
    if (SCH_tasks_G[0].pTask && SCH_tasks_G[0].RunMe == 0) {
        if (SCH_tasks_G[0].Delay > 0) SCH_tasks_G[0].Delay--;
        if (SCH_tasks_G[0].Delay == 0) SCH_tasks_G[0].RunMe = 1;
    }
}

void SCH_Dispatch_Tasks(void) {
	if(SCH_tasks_G[0].RunMe > 0){
		(*SCH_tasks_G[0].pTask)();
		SCH_tasks_G[0].RunMe = 0;
		sTask temp = SCH_tasks_G[0];
		SCH_Delete_Task(temp.TaskID);
		if (temp.Period > 0) {
			SCH_Add_Task(temp.pTask, temp.Period, temp.Period);
		}
	}
}


#endif /* SRC_SCHEDULER_C_ */
