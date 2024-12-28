/**
 * @file communication.c
 * @author Antoni Wielgus
 * @date 10-11-2024
 */

#include "communication.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "usart.h"

uint8_t sender_buffer[BUFFER_SIZE] = {0};
uint8_t receiveing_buffer[RECEIVEING_BUFFER_SIZE] = {0};

void set_can_ID(uint8_t can_ID)
{
    sender_buffer[0] = can_ID;
}

void send_buffer(UART_HandleTypeDef *uart)
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

float uint_to_float(int x_int, float x_min, float x_max, int bits)
{
    /// converts unsigned int to float, given range and number of bits ///
    float span = x_max - x_min;
    float offset = x_min;
    return ((float)x_int) * span / ((float)((1 << bits) - 1)) + offset;
}

void parse_uart_buffer(uint8_t *data, uint8_t *id_, float *p_, float *v_, float *i_, uint8_t *T_)
{
    int id = data[0]; // Driver ID
    int p_int = (data[1] << 8) | data[2];
    int v_int = (data[3] << 4) | (data[4] >> 4);
    int i_int = ((data[4] & 0xF) << 8) | data[5];
    int T_int = data[6];

    *id_ = id;
    *p_ = (uint_to_float(p_int, -12.5, 12.5, 16));
    *v_ = (uint_to_float(v_int, -30.0, 30.0, 12));
    *i_ = (uint_to_float(i_int, -5.0, 5.0, 12));
    *T_ = T_int;

    char str[5];

    char msg[64]; // debug usart1 message frame
    sprintf(msg, "P: %d, V: %d, I: %d\n\r", (uint32_t)p_int, (int32_t)v_int, (int32_t)i_int);
    HAL_UART_Transmit(&huart1, (uint8_t *)msg, strlen(msg), 1000);
}
