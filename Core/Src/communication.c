/**
 * @file communication.c
 * @author Antoni Wielgus
 * @date 10-11-2024
 */

#include "communication.h"


uint8_t sender_buffer[BUFFER_SIZE] = {0};


void set_can_ID(uint8_t can_ID)
{
    sender_buffer[0] = can_ID;
}

void send_buffer(UART_HandleTypeDef* uart)
{
    HAL_UART_Transmit(uart, sender_buffer, BUFFER_SIZE, HAL_MAX_DELAY);
}

void start_engin()
{
    sender_buffer[1] = 0x01;
}

void stop_engin()
{
    sender_buffer[1] = 0x00;
}




void load_data(float p_, float v_, float kp_, float kd_, float t_)
{
    union Float_to_uint8_array my_union;

    // motor is already running
    sender_buffer[1] = 0x02;

    uint8_t i = 2;

    my_union.float_value = p_;
    for (uint8_t c = 0; c < 4; c++)
        sender_buffer[i++] = my_union.uint8_t_array[c];

    my_union.float_value = v_;
    for (uint8_t c = 0; c < 4; c++)
        sender_buffer[i++] = my_union.uint8_t_array[c];

    my_union.float_value = kp_;
    for (uint8_t c = 0; c < 4; c++)
        sender_buffer[i++] = my_union.uint8_t_array[c];

    my_union.float_value = kd_;
    for (uint8_t c = 0; c < 4; c++)
        sender_buffer[i++] = my_union.uint8_t_array[c];

    my_union.float_value = t_;
    for (uint8_t c = 0; c < 4; c++)
        sender_buffer[i++] = my_union.uint8_t_array[c];
}