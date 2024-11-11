/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma2d.h"
#include "i2c.h"
#include "ltdc.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "fmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lcd_menu.h"
#include "communication.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint16_t encoder_previous_count = 0;

char msg[64];   // debug usart1 message frame
uint32_t count; // encoder counter
uint8_t menu_choice = 0;
enum Main_menu_type actual_menu_type = MAIN;

// parameters
int16_t p = 0;
int16_t v = 0;
int32_t kp = 0;
int16_t kd = 0;
int16_t t = 0;

// parameters constraints
const int16_t P_MAX = 1250;
const int16_t P_MIN = -1250;

const int16_t V_MAX = 4500;
const int16_t V_MIN = -4500;

const int16_t T_MAX = 1800;
const int16_t T_MIN = -1800;

const int32_t KP_MAX = 50000;
const int8_t KP_MIN = 0;

const int16_t KD_MAX = 500;
const int8_t KD_MIN = 0;

// can ID
uint8_t can_id = 0;

const uint8_t CAN_ID_MAX = 12;
const uint8_t CAN_ID_MIN = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

// this function is used to refresh p, v, Kp, Kd, t parameters
void refresh_parameters();

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA2D_Init();
  MX_FMC_Init();
  MX_I2C3_Init();
  MX_LTDC_Init();
  MX_SPI5_Init();
  MX_USART1_UART_Init();
  MX_TIM3_Init();
  MX_UART5_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  lcd_initialization();

  HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
  HAL_Delay(1000);
  // lcd_main_menu(actual_menu_type);

  while (1)
  {
    count = __HAL_TIM_GET_COUNTER(&htim3);
    count /= 2;

    refresh_parameters();

    // sprintf((char *)msg, "Encoder: %d, P: %d, V: %d\n\r", count, p, v);
    // HAL_UART_Transmit(&huart1, (uint8_t *)msg, strlen(msg), 1000);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_14);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 360;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
uint32_t previousTime = 0;
uint32_t currentTime = 0;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  currentTime = HAL_GetTick();

  if (GPIO_Pin == encoder_button_Pin && (currentTime - previousTime > 100))
  {
    previousTime = currentTime;

    HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_13);

    if (actual_menu_type == MAIN)
    {
      if (menu_choice > 2)
        menu_choice = 0;
      else
        menu_choice++;
    }

    if (actual_menu_type == PARAMETERS)
    {
      if (menu_choice > 8)
        menu_choice = 0;
      else
        menu_choice++;
    }
  }

  if (GPIO_Pin == confirm_button_Pin && (currentTime - previousTime > 100))
  {
    previousTime = currentTime;

    if (actual_menu_type == MAIN)
    {
      actual_menu_type = menu_choice + 1;
      menu_choice = 0;
    }

    if (actual_menu_type == PARAMETERS && menu_choice == 8)
    {
      actual_menu_type = MAIN;
      menu_choice = 0;
    }

    // start motor
    if (actual_menu_type == PARAMETERS && menu_choice == 5)
    { 
      set_can_ID(can_id);
      start_engin();
      send_buffer(&huart5);
    }

    // stop motor
    if (actual_menu_type == PARAMETERS && menu_choice == 6)
    {
      set_can_ID(can_id);
      stop_engin();
      send_buffer(&huart5);
    }

    // send data
    if (actual_menu_type == PARAMETERS && menu_choice == 7)
    {
      load_data();
      send_buffer(&huart5);
    }

    HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_13);
  }

  if (GPIO_Pin == encoder_interrupt_Pin)
  {
    // useful to debug
    // sprintf((char *)msg, "Encoder: %d, Different: %d, P: %d, V: %d, flag: %d\n\r", count, counter_different, p, v, addition_flag);
    // HAL_UART_Transmit(&huart1, (uint8_t *)msg, strlen(msg), 1000);
  }

  lcd_refresh_UJ(actual_menu_type, menu_choice);
}

void refresh_parameters()
{
  int16_t counter_different = count - encoder_previous_count;

  // when occures overload of encoder rotation counter 
  if (abs(counter_different) > 50)
    counter_different = 1;

  int8_t addition_flag = 1;
  if (counter_different < 0)
  {
    addition_flag = -1;
    counter_different *= -1;
  }

  // for P value
  if (actual_menu_type == PARAMETERS && menu_choice == 0)
  {
    p += (10 * counter_different * addition_flag);

    if (p > P_MAX)
      p = P_MAX;

    if (p < P_MIN)
      p = P_MIN;
  }

  // for V value
  if (actual_menu_type == PARAMETERS && menu_choice == 1)
  {
    v += (10 * counter_different * addition_flag);

    if (v > V_MAX)
      v = V_MAX;
    
    if (v < V_MIN)
      v = V_MIN;
  }

  // for Kp value
  if (actual_menu_type == PARAMETERS && menu_choice == 2)
  {
    kp += (10 * counter_different * addition_flag);

    if (kp > KP_MAX)
      kp = KP_MAX;

    if (kp < KP_MIN)
      kp = KP_MIN;
  }

  // for KD value
  if (actual_menu_type == PARAMETERS && menu_choice == 3)
  {
    kd += (10 * counter_different * addition_flag);

    if (kd > KD_MAX)
      kd = KD_MAX;

    if (kd < KD_MIN)
      kd = KD_MIN;
  }

  // for t value
  if (actual_menu_type == PARAMETERS && menu_choice == 4)
  {
    t += (10 * counter_different * addition_flag);

    if (t > T_MAX)
      t = T_MAX;

    if (t < T_MIN)
      t = T_MIN;
  }

  // for increasing or decreasing can id
  if (actual_menu_type == MAIN && menu_choice == 3)
  {
    can_id += counter_different * addition_flag;

    if (can_id > CAN_ID_MAX)
      can_id = CAN_ID_MAX;
  }

  if (counter_different != 0)
    lcd_refresh_UJ(actual_menu_type, menu_choice);

  encoder_previous_count = count;
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
