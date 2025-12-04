/*
 * normalTraffic.c
 *
 *  Created on: Nov 3, 2025
 *      Author: Hoàng Hưng
 */

#include "normalTraffic.h"

void normalTraffic_run(){
	switch(mode){
		case INIT:
			mode = NORMAL_RED_GREEN;
			setTimer(0, green_time*1000);
			tmp_time = red_time;
			setTimer(1, 10);
			break;
		case NORMAL_RED_GREEN:
			HAL_GPIO_WritePin(xLED1_GPIO_Port, xLED1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(xLED2_GPIO_Port, xLED2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(yLED1_GPIO_Port, yLED1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(yLED2_GPIO_Port, yLED2_Pin, GPIO_PIN_RESET);

			if(isTimerExpired(1)){
				Traffic_Display_Update("DEN DO  :   ", tmp_time--);
				setTimer(1, 1000);
			}

			if(isTimerExpired(0)){
					mode = NORMAL_RED_AMBER;
					setTimer(0, amber_time*1000);
			}

			if(isButtonPressed(3)){
				mode = MANUAL_RED_GREEN;
				Traffic_Display_Manual("MANUAL MODE", "DEN DO   ");
			}

			if(isButtonPressed(0)){
				mode = MODE2_MOD_RED;
				setTimer(0, 250);
				tmp_time = red_time;
				setTimer(1, 10);
				HAL_GPIO_WritePin(xLED1_GPIO_Port, xLED1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(xLED2_GPIO_Port, xLED2_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(yLED1_GPIO_Port, yLED1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(yLED2_GPIO_Port, yLED2_Pin, GPIO_PIN_RESET);
			}

			break;
		case NORMAL_RED_AMBER:
			HAL_GPIO_WritePin(xLED1_GPIO_Port, xLED1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(xLED2_GPIO_Port, xLED2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(yLED1_GPIO_Port, yLED1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(yLED2_GPIO_Port, yLED2_Pin, GPIO_PIN_SET);

			if(isTimerExpired(1)){
							Traffic_Display_Update("DEN DO  :    ", tmp_time--);
							setTimer(1, 1000);
						}

			if(isTimerExpired(0)){
				mode = NORMAL_GREEN_RED;
				setTimer(0, green_time*1000);
				tmp_time = green_time;
			}

			if(isButtonPressed(3)){
				mode = MANUAL_RED_AMBER;
				Traffic_Display_Manual("MANUAL MODE", "DEN DO   ");
				setTimer(1, 2000);
			}

			if(isButtonPressed(0)){
				mode = MODE2_MOD_RED;
				setTimer(0, 250);
				tmp_time = red_time;
				setTimer(1, 10);
				HAL_GPIO_WritePin(xLED1_GPIO_Port, xLED1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(xLED2_GPIO_Port, xLED2_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(yLED1_GPIO_Port, yLED1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(yLED2_GPIO_Port, yLED2_Pin, GPIO_PIN_RESET);
			}
			break;
		case NORMAL_GREEN_RED:
			HAL_GPIO_WritePin(xLED1_GPIO_Port, xLED1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(xLED2_GPIO_Port, xLED2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(yLED1_GPIO_Port, yLED1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(yLED2_GPIO_Port, yLED2_Pin, GPIO_PIN_SET);

			if(isTimerExpired(1)){
				Traffic_Display_Update("DEN XANH:     ", tmp_time--);
				setTimer(1, 1000);
			}

			if(isTimerExpired(0)){
				mode = NORMAL_AMBER_RED;
				setTimer(0, amber_time*1000);
				tmp_time = amber_time;
			}

			if(isButtonPressed(3)){
				mode = MANUAL_GREEN_RED;
				Traffic_Display_Manual("MANUAL MODE", "DEN XANH ");
			}

			if(isButtonPressed(0)){
				mode = MODE2_MOD_RED;
				setTimer(0, 250);
				tmp_time = red_time;
				setTimer(1, 10);
				HAL_GPIO_WritePin(xLED1_GPIO_Port, xLED1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(xLED2_GPIO_Port, xLED2_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(yLED1_GPIO_Port, yLED1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(yLED2_GPIO_Port, yLED2_Pin, GPIO_PIN_RESET);
			}
			break;
		case NORMAL_AMBER_RED:
			HAL_GPIO_WritePin(xLED1_GPIO_Port, xLED1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(xLED2_GPIO_Port, xLED2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(yLED1_GPIO_Port, yLED1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(yLED2_GPIO_Port, yLED2_Pin, GPIO_PIN_SET);


			if(isTimerExpired(1)){
				Traffic_Display_Update("DEN VANG:    ", tmp_time--);
				setTimer(1, 1000);
			}

			if(isTimerExpired(0)){
				mode = NORMAL_RED_GREEN;
				tmp_time = red_time;
				setTimer(0, green_time*1000);
			}

			if(isButtonPressed(3)){
				mode = MANUAL_AMBER_RED;
				Traffic_Display_Manual("MANUAL MODE", "DEN VANG ");
				setTimer(1, 2000);
			}

			if(isButtonPressed(0)){
				mode = MODE2_MOD_RED;
				setTimer(0, 250);
				tmp_time = red_time;
				setTimer(1, 10);
				HAL_GPIO_WritePin(xLED1_GPIO_Port, xLED1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(xLED2_GPIO_Port, xLED2_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(yLED1_GPIO_Port, yLED1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(yLED2_GPIO_Port, yLED2_Pin, GPIO_PIN_RESET);
			}
			break;
		default:
			break;
	}
}
