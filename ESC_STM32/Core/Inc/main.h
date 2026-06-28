/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "stm32u5xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "mydriver.h"
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
#define DIR3_1_Pin GPIO_PIN_1
#define DIR3_1_GPIO_Port GPIOC
#define DIR3_0_Pin GPIO_PIN_2
#define DIR3_0_GPIO_Port GPIOC
#define PUL3_Pin GPIO_PIN_3
#define PUL3_GPIO_Port GPIOC
#define DIR1_1_Pin GPIO_PIN_0
#define DIR1_1_GPIO_Port GPIOA
#define DIR1_0_Pin GPIO_PIN_1
#define DIR1_0_GPIO_Port GPIOA
#define PUL1_Pin GPIO_PIN_2
#define PUL1_GPIO_Port GPIOA
#define DIR2_1_Pin GPIO_PIN_3
#define DIR2_1_GPIO_Port GPIOA
#define DIR2_0_Pin GPIO_PIN_4
#define DIR2_0_GPIO_Port GPIOA
#define PUL2_Pin GPIO_PIN_5
#define PUL2_GPIO_Port GPIOA
#define motor_control_Pin GPIO_PIN_4
#define motor_control_GPIO_Port GPIOC

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
