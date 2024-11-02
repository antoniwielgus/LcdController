/**
 * @file lcd_menu.c
 * @author Antoni Wielgus
 * @date 02-11-2024
 */

#include "lcd_menu.h"

#include "stm32f429i_discovery_lcd.h"

void lcd_initialization()
{
    BSP_LCD_Init();
    BSP_LCD_LayerDefaultInit(LCD_BACKGROUND_LAYER, LCD_FRAME_BUFFER);
    BSP_LCD_Clear(LCD_COLOR_CYAN);
    BSP_LCD_DisplayStringAtLine(0, (uint8_t *)"Hello world2!");
}

void lcd_refresh_UJ(enum Main_menu_type actual, uint8_t choice)
{
    switch (actual)
    {
    case MAIN:
        lcd_main_menu(choice);
        break;

    case PARAMETERS:
        // lcd_parameters_type(choice);
        break;

    case MOVEMENT:
        // lcd_movment_type(choice);
        break;

    case SENSORS:
        // lcd_sensors_type(choice);
        break;
    
    default:
        break;
    }
}

void lcd_main_menu(uint8_t choice)
{
    BSP_LCD_Clear(LCD_COLOR_WHITE);

    switch (choice)
    {
    case 0: // parameters
        BSP_LCD_SetTextColor(LCD_COLOR_RED);
        BSP_LCD_DisplayStringAtLine(0, (uint8_t *)"PARAMETERS");
        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
        BSP_LCD_DisplayStringAtLine(1, (uint8_t *)"MOVEMENT");
        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
        BSP_LCD_DisplayStringAtLine(2, (uint8_t *)"SENSORS");
        break;
    case 1: // movement
        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
        BSP_LCD_DisplayStringAtLine(0, (uint8_t *)"PARAMETERS");
        BSP_LCD_SetTextColor(LCD_COLOR_RED);
        BSP_LCD_DisplayStringAtLine(1, (uint8_t *)"MOVEMENT");
        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
        BSP_LCD_DisplayStringAtLine(2, (uint8_t *)"SENSORS");
        break;
    case 2: // sensors
        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
        BSP_LCD_DisplayStringAtLine(0, (uint8_t *)"PARAMETERS");
        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
        BSP_LCD_DisplayStringAtLine(1, (uint8_t *)"MOVEMENT");
        BSP_LCD_SetTextColor(LCD_COLOR_RED);
        BSP_LCD_DisplayStringAtLine(2, (uint8_t *)"SENSORS");
        break;
    default:
        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
        BSP_LCD_DisplayStringAtLine(0, (uint8_t *)"PARAMETERS");
        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
        BSP_LCD_DisplayStringAtLine(1, (uint8_t *)"MOVEMENT");
        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
        BSP_LCD_DisplayStringAtLine(2, (uint8_t *)"SENSORS");
        break;
    }

    // BSP_LCD_Clear(LCD_COLOR_GREEN);
    // BSP_LCD_DisplayStringAtLine(0, (uint8_t *)"PARAMETERS");
    // BSP_LCD_DisplayStringAtLine(1, (uint8_t *)"MOVEMENT");
    // BSP_LCD_DisplayStringAtLine(0, (uint8_t *)"SENSORS");
}
