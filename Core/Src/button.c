/*
 * button.c
 *
 *  Created on: Oct 16, 2025
 *      Author: Hoàng Hưng
 */

#include "button.h"

#define LONG_PRESS_TIME 100

GPIO_TypeDef* BUTTON_PORT[N_BUTTONS] = {BUTTON1_GPIO_Port, BUTTON2_GPIO_Port, BUTTON3_GPIO_Port, BUTTON4_GPIO_Port};
uint16_t BUTTON_PIN[N_BUTTONS] = {BUTTON1_Pin, BUTTON2_Pin, BUTTON3_Pin, BUTTON4_Pin};

int KeyReg0[N_BUTTONS];
int KeyReg1[N_BUTTONS];
int KeyReg2[N_BUTTONS];
int KeyReg3[N_BUTTONS];

int TimeOutForKeyPress[N_BUTTONS];
int button_flag[N_BUTTONS];
int button_long_flag[N_BUTTONS];

void subKeyProcess(int index) {
	button_flag[index] = 1;
}

int isButtonPressed(int index) {
	if (button_flag[index] == 1) {
		button_flag[index] = 0;
		return 1;
	}
	return 0;
}

int isButtonLongPressed(int index) {
	if (button_long_flag[index] == 1) {
		button_long_flag[index] = 0;
		return 1;
	}
	return 0;
}

void getKeyInput() {
	for(int i = 0; i < N_BUTTONS; i++) {
		KeyReg2[i] = KeyReg1[i];
		KeyReg1[i] = KeyReg0[i];
		KeyReg0[i] = HAL_GPIO_ReadPin(BUTTON_PORT[i], BUTTON_PIN[i]);

		if ((KeyReg0[i] == KeyReg1[i]) && (KeyReg1[i] == KeyReg2[i])) {
			if (KeyReg3[i] != KeyReg2[i]) {
				KeyReg3[i] = KeyReg2[i];

				if (KeyReg3[i] == PRESSED_STATE) {
					TimeOutForKeyPress[i] = LONG_PRESS_TIME;
					subKeyProcess(i);
				}
			} else {
				if (KeyReg3[i] == PRESSED_STATE) {
					if (TimeOutForKeyPress[i] > 0) {
						TimeOutForKeyPress[i]--;
						if (TimeOutForKeyPress[i] == 0) {
							button_long_flag[i] = 1;
							TimeOutForKeyPress[i] = LONG_PRESS_TIME;
						}
					}
				}
			}
		}
	}
}
