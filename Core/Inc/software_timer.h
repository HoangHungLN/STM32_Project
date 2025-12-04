/*
 * software_timer.h
 *
 *  Created on: Sep 25, 2025
 *      Author: Hoàng Hưng
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#define MAX_TIMER 20

extern int timer_flag[MAX_TIMER];
extern int timer_counter[MAX_TIMER];

void setTimer(int indexi, int duration);
int isTimerExpired(int index);
void timerRun();

#endif /* INC_SOFTWARE_TIMER_H_ */
