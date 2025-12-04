/*
 * button.h
 *
 *  Created on: Oct 16, 2025
 *      Author: Hoàng Hưng
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"

#define NORMAL_STATE	GPIO_PIN_SET
#define PRESSED_STATE	GPIO_PIN_RESET
#define N_BUTTONS 4

extern int button_flag[N_BUTTONS];
extern int button_long_flag[N_BUTTONS];

void getKeyInput();
int isButtonPressed(int index);
int isButtonLongPressed(int index);

#endif /* INC_BUTTON_H_ */
