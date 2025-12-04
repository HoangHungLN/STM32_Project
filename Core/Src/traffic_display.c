/*
 * traffic_display.c
 *
 *  Created on: Nov 29, 2025
 *      Author: Admin
 */

#include "traffic_display.h"
#include "i2c-lcd.h"
#include <stdio.h>

void Traffic_Display_Init(void) {
    lcd_init();
    lcd_clear_display();
    lcd_goto_XY(1, 0);
    lcd_send_string(" Traffic System");
    HAL_Delay(1000);
    lcd_clear_display();
}


void Traffic_Display_Update(char *label, int time){
    char buffer[16];
    lcd_goto_XY(1, 0);
    lcd_send_string(label);

    sprintf(buffer, "Time: %02ds", time);
    lcd_goto_XY(2, 0);
    lcd_send_string(buffer);
}

void Traffic_Display_Manual(char *label1, char *label2){
    lcd_goto_XY(1, 0);
    lcd_send_string(label1);

    lcd_goto_XY(2, 0);
    lcd_send_string(label2);


}
