/*
 * traffic_display.h
 *
 *  Created on: Nov 29, 2025
 *      Author: Admin
 */

#ifndef INC_TRAFFIC_DISPLAY_H_
#define INC_TRAFFIC_DISPLAY_H_

#include "stm32f1xx_hal.h"

void Traffic_Display_Init(void);
void Traffic_Display_Update(char *label, int time);
void Traffic_Display_Manual(char *label1, char *label2);

#endif /* INC_TRAFFIC_DISPLAY_H_ */
