/*
 * global.h
 *
 *  Created on: Oct 24, 2025
 *      Author: Hoàng Hưng
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "button.h"
#include "software_timer.h"
#include "main.h"
#include "traffic_display.h"

#define INIT				0
#define NORMAL_RED_GREEN	1
#define NORMAL_RED_AMBER 	2
#define NORMAL_GREEN_RED 	3
#define NORMAL_AMBER_RED 	4

#define MANUAL_RED_GREEN	101
#define MANUAL_RED_AMBER	102
#define MANUAL_GREEN_RED	103
#define MANUAL_AMBER_RED	104

#define MODE2_MOD_RED		201
#define MODE3_MOD_AMBER 	202
#define MODE4_MOD_GREEN 	203

extern int mode;

extern int red_time;
extern int amber_time;
extern int green_time;
extern int tmp_time;

#endif /* INC_GLOBAL_H_ */
