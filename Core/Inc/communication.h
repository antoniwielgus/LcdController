/**
 * @file communication.h
 * @author Antoni Wielgus
 * @brief
 * @date 10-11-2024
 */

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "main.h"

#include "stdio.h"
#include "string.h"
#include "stdlib.h"


#define BUFFER_SIZE 23
#define RECEIVEING_BUFFER_SIZE 8

extern uint8_t sender_buffer[BUFFER_SIZE];
extern uint8_t receiveing_buffer[RECEIVEING_BUFFER_SIZE];

union Float_to_uint8_array
{
    float float_value;
    uint8_t uint8_t_array[4];
};

void set_can_ID(uint8_t can_ID);
void send_buffer(UART_HandleTypeDef* uart);
void start_engin();
void stop_engin();

void load_data(float p_, float v_, float kp_, float kd_, float t_);

float uint_to_float(int x_int, float x_min, float x_max, int bits);
void parse_uart_buffer(uint8_t *data, uint8_t* id_, float* p_, float* v_, float* i_, uint8_t* T_);


#endif