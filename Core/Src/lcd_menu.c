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
        lcd_parameters_type(choice);
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
}

void lcd_parameters_type(uint8_t choice)
{
    BSP_LCD_Clear(LCD_COLOR_WHITE);

    BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
    BSP_LCD_DisplayStringAtLine(0, (uint8_t *)"__PARAMETERS__");

    uint32_t color0 = LCD_COLOR_BLACK;
    uint32_t color1 = LCD_COLOR_BLACK;
    uint32_t color2 = LCD_COLOR_BLACK;
    uint32_t color3 = LCD_COLOR_BLACK;
    uint32_t color4 = LCD_COLOR_BLACK;
    uint32_t color5 = LCD_COLOR_BLACK;
    uint32_t color6 = LCD_COLOR_BLACK;
    uint32_t color7 = LCD_COLOR_BLACK;
    uint32_t color8 = LCD_COLOR_BLACK;

    switch (choice)
    {
    case 0:
        color0 = LCD_COLOR_RED;
        break;
    case 1:
        color1 = LCD_COLOR_RED;
        break;
    case 2:
        color2 = LCD_COLOR_RED;
        break;
    case 3:
        color3 = LCD_COLOR_RED;
        break;
    case 4:
        color4 = LCD_COLOR_RED;
        break;
    case 5:
        color5 = LCD_COLOR_RED;
        break;
    case 6:
        color6 = LCD_COLOR_RED;
        break;
    case 7:
        color7 = LCD_COLOR_RED;
        break;
    case 8:
        color8 = LCD_COLOR_RED;
        break;
    default:
        break;
    }

    char message[64];
    char float_char[6];

    BSP_LCD_SetTextColor(color0);
    float_to_char_array(float_char, p);
    sprintf(message, "P: %s", float_char);
    BSP_LCD_DisplayStringAtLine(1, message);

    BSP_LCD_SetTextColor(color1);
    float_to_char_array(float_char, v);
    sprintf(message, "V: %s", float_char);
    BSP_LCD_DisplayStringAtLine(2, message);

    BSP_LCD_SetTextColor(color2);
    float_to_char_array(float_char, kp);
    sprintf(message, "Kp: %s", float_char);
    BSP_LCD_DisplayStringAtLine(3, message);

    BSP_LCD_SetTextColor(color3);
    float_to_char_array(float_char, kd);
    sprintf(message, "Kd: %s", float_char);
    BSP_LCD_DisplayStringAtLine(4, message);

    BSP_LCD_SetTextColor(color4);
    float_to_char_array(float_char, t);
    sprintf(message, "V: %s", float_char);
    BSP_LCD_DisplayStringAtLine(5, message);

    BSP_LCD_SetTextColor(color5);
    BSP_LCD_DisplayStringAtLine(6, (uint8_t *)"Start motor");

    BSP_LCD_SetTextColor(color6);
    BSP_LCD_DisplayStringAtLine(7, (uint8_t *)"Stop motor");

    BSP_LCD_SetTextColor(color7);
    BSP_LCD_DisplayStringAtLine(8, (uint8_t *)"Send data");

    BSP_LCD_SetTextColor(color8);
    BSP_LCD_DisplayStringAtLine(9, (uint8_t *)"BACK");
}

void float_to_char_array(char *destination, uint16_t value)
{
    char val[6];

    sprintf(val, "%d", value);

    if (value < 100)
        sprintf(destination, "0,%c%c%c%c%c", val[0], val[1], val[2], val[3], val[4]);
    else if (value < 1000)
        sprintf(destination, "%c,%c%c%c%c", val[0], val[1], val[2], val[3], val[4]);
    else if (value < 10000)
        sprintf(destination, "%c%c,%c%c%c", val[0], val[1], val[2], val[3], val[4]);
    else if (value < 100000)
        sprintf(destination, "%c%c%c,%c%c", val[0], val[1], val[2], val[3], val[4]);
}
