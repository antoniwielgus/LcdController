/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define encoder_interrupt_Pin GPIO_PIN_6
#define encoder_interrupt_GPIO_Port GPIOF
#define encoder_interrupt_EXTI_IRQn EXTI9_5_IRQn
#define confirm_button_Pin GPIO_PIN_0
#define confirm_button_GPIO_Port GPIOA
#define confirm_button_EXTI_IRQn EXTI0_IRQn
#define encoder_button_Pin GPIO_PIN_5
#define encoder_button_GPIO_Port GPIOA
#define encoder_button_EXTI_IRQn EXTI9_5_IRQn

/* USER CODE BEGIN Private defines */

// global variables
extern int16_t p;
extern int16_t v;
extern int32_t kp;
extern int16_t kd;
extern int16_t t;

extern int16_t angle;

extern uint8_t can_id;

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
