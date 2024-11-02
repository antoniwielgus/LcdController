/**
 * @file lcd_menu.h
 * @author Antoni Wielgus
 * @brief functions whitch represents different types of menu
 * @date 02-11-2024
 */

#ifndef LCD_MENU_H
#define LCD_MENU_H

#include "main.h"


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




#endif