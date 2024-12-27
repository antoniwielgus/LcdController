/**
 * @file lcd_menu.h
 * @author Antoni Wielgus
 * @brief functions whitch represents different types of menu
 * @date 02-11-2024
 */

#ifndef LCD_MENU_H
#define LCD_MENU_H

#include "main.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"


// const uint8_t buffer_size = 64;
// char message[buffer_size];

enum Main_menu_type
{
    MAIN,
    PARAMETERS,
    MOVEMENT,
    SENSORS
};


void lcd_initialization();
void lcd_refresh_UJ(enum Main_menu_type actual, uint8_t choice);
void lcd_main_menu(uint8_t choice);
void lcd_parameters_type(uint8_t choice);
void lcd_movment_type(uint8_t choice);
void lcd_sensors_type(uint8_t choice);

void int32_t_to_char_array(char* destination, int32_t value);
void float_to_char_array_(char* destination, float value);




#endif