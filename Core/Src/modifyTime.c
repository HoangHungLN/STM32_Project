/*
 * modifyTime.c
 *
 *  Created on: Nov 5, 2025
 *      Author: Hoàng Hưng
 */

#include "modifyTime.h"

void modifyTime_run(){
	switch(mode){
		case MODE2_MOD_RED:
			if(isTimerExpired(0)){
				setTimer(0, 250);
				HAL_GPIO_TogglePin(xLED1_GPIO_Port, xLED1_Pin);
				HAL_GPIO_TogglePin(xLED2_GPIO_Port, xLED2_Pin);
				HAL_GPIO_TogglePin(yLED1_GPIO_Port, yLED1_Pin);
				HAL_GPIO_TogglePin(yLED2_GPIO_Port, yLED2_Pin);
			}

			if(isTimerExpired(1)){
				Traffic_Display_Update("DEN DO  : ", tmp_time);
				setTimer(1, 1000);
			}

			if(isButtonPressed(1)){
				tmp_time = (tmp_time + 1) % 100;
			}

			if(isButtonPressed(2)){
				red_time = tmp_time;
			}

			if(isButtonPressed(0)){
				mode = MODE3_MOD_AMBER;
				setTimer(0, 250);
				tmp_time = amber_time;
				setTimer(1, 10);
				HAL_GPIO_WritePin(xLED1_GPIO_Port, xLED1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(xLED2_GPIO_Port, xLED2_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(yLED1_GPIO_Port, yLED1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(yLED2_GPIO_Port, yLED2_Pin, GPIO_PIN_RESET);
			}
			break;
		case MODE3_MOD_AMBER:
			if(isTimerExpired(0)){
				setTimer(0, 250);
				HAL_GPIO_TogglePin(xLED2_GPIO_Port, xLED2_Pin);
				HAL_GPIO_TogglePin(yLED2_GPIO_Port, yLED2_Pin);
			}

			if(isTimerExpired(1)){
				Traffic_Display_Update("DEN VANG: ", tmp_time);
				setTimer(1, 1000);
			}

			if(isButtonPressed(1)){
				tmp_time = (tmp_time + 1) % 100;
			}

			if(isButtonPressed(2)){
				amber_time = tmp_time;
			}

			if(isButtonPressed(0)){
				mode = MODE4_MOD_GREEN;
				setTimer(0, 250);
				tmp_time = green_time;
				setTimer(1, 10);
				HAL_GPIO_WritePin(xLED1_GPIO_Port, xLED1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(xLED2_GPIO_Port, xLED2_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(yLED1_GPIO_Port, yLED1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(yLED2_GPIO_Port, yLED2_Pin, GPIO_PIN_RESET);
			}
			break;
		case MODE4_MOD_GREEN:
			if(isTimerExpired(0)){
				setTimer(0, 250);
				HAL_GPIO_TogglePin(xLED1_GPIO_Port, xLED1_Pin);
				HAL_GPIO_TogglePin(yLED1_GPIO_Port, yLED1_Pin);
			}

			if(isTimerExpired(1)){
				Traffic_Display_Update("DEN XANH: ", tmp_time);
				setTimer(1, 1000);
			}

			if(isButtonPressed(1)){
				tmp_time = (tmp_time + 1) % 100;
			}

			if(isButtonPressed(2)){
				green_time = tmp_time;
			}

			if(isButtonPressed(0)){
				modifyWrongTime();
				mode = NORMAL_RED_GREEN;
				setTimer(0, green_time*1000);
				tmp_time = red_time;
				setTimer(1, 10);
			}
			break;
		default:
			break;
	}
}

void modifyWrongTime(){
	if(green_time + amber_time < red_time){
		green_time = green_time + (red_time - (amber_time + green_time));
	}
	if(green_time + amber_time > red_time){
		red_time = red_time + ((green_time + amber_time) - red_time);
	}
}
