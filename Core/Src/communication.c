/**
 * @file communication.c
 * @author Antoni Wielgus
 * @date 10-11-2024
 */

#include "communication.h"


const uint8_t buffer_size = 23;
uint8_t sender_buffer[23] = {0};


void set_can_ID(uint8_t can_ID)
{
    sender_buffer[0] = can_ID;
}

void send_buffer(UART_HandleTypeDef* uart)
{
    HAL_UART_Transmit(uart, sender_buffer, buffer_size, HAL_MAX_DELAY);
}

void start_engin()
{
    sender_buffer[1] = 0x01;
}

void stop_engin()
{
    sender_buffer[1] = 0x00;
}