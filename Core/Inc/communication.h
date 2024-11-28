/**
 * @file communication.h
 * @author Antoni Wielgus
 * @brief
 * @date 10-11-2024
 */

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "main.h"


#define BUFFER_SIZE 23
extern uint8_t sender_buffer[BUFFER_SIZE];

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


#endif