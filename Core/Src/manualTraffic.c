/*
 * manualTraffic.c
 *
 *  Created on: Nov 4, 2025
 *      Author: Hoàng Hưng
 */

#include "manualTraffic.h"

void manualTrafic_run(){
	switch (mode){
		case MANUAL_RED_GREEN:
			HAL_GPIO_WritePin(xLED1_GPIO_Port, xLED1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(xLED2_GPIO_Port, xLED2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(yLED1_GPIO_Port, yLED1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(yLED2_GPIO_Port, yLED2_Pin, GPIO_PIN_RESET);

			if(isButtonPressed(1)){
				mode = MANUAL_RED_AMBER;
				setTimer(2, 2000);
			}

			if(isButtonPressed(2)){
				mode = NORMAL_RED_GREEN;
				tmp_time = red_time;
				setTimer(0, green_time*1000);
				setTimer(1, 10);
			}
			break;
		case MANUAL_RED_AMBER:
			HAL_GPIO_WritePin(xLED1_GPIO_Port, xLED1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(xLED2_GPIO_Port, xLED2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(yLED1_GPIO_Port, yLED1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(yLED2_GPIO_Port, yLED2_Pin, GPIO_PIN_SET);

			if(isTimerExpired(2)){
				mode = MANUAL_GREEN_RED;
				Traffic_Display_Manual("MANUAL MODE", "DEN XANH ");
			}

			if(isButtonPressed(2)){
				mode = NORMAL_RED_AMBER;
				setTimer(0, amber_time*1000);
				tmp_time = amber_time;
				setTimer(1, 10);
			}
			break;
		case MANUAL_GREEN_RED:
			HAL_GPIO_WritePin(xLED1_GPIO_Port, xLED1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(xLED2_GPIO_Port, xLED2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(yLED1_GPIO_Port, yLED1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(yLED2_GPIO_Port, yLED2_Pin, GPIO_PIN_SET);

			if(isButtonPressed(1)){
				mode = MANUAL_AMBER_RED;
				setTimer(2, 2000);
				Traffic_Display_Manual("MANUAL MODE", "DEN VANG ");
			}

			if(isButtonPressed(2)){
				mode = NORMAL_GREEN_RED;
				setTimer(0, green_time*1000);
				tmp_time = green_time;
				setTimer(1, 10);
			}
			break;
		case MANUAL_AMBER_RED:
			HAL_GPIO_WritePin(xLED1_GPIO_Port, xLED1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(xLED2_GPIO_Port, xLED2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(yLED1_GPIO_Port, yLED1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(yLED2_GPIO_Port, yLED2_Pin, GPIO_PIN_SET);

			if(isTimerExpired(2)){
				mode = MANUAL_RED_GREEN;
				Traffic_Display_Manual("MANUAL MODE", "DEN DO   ");
			}

			if(isButtonPressed(2)){
				mode = NORMAL_AMBER_RED;
				setTimer(0, amber_time*1000);
				tmp_time = amber_time;
				setTimer(1, 10);
			}
			break;
		default:
			break;

	}
}
