/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : app_freertos.c
  * Description        : FreeRTOS applicative file
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

/* Includes ------------------------------------------------------------------*/
#include "app_freertos.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "main.h"
#include "tim.h"
#include "adc.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticTask_t osStaticThreadDef_t;
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
uint32_t MyBufferTask00[ 128 ];
osStaticThreadDef_t MycontrolBlocTask00;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_mem = &MyBufferTask00[0],
  .stack_size = sizeof(MyBufferTask00),
  .cb_mem = &MycontrolBlocTask00,
  .cb_size = sizeof(MycontrolBlocTask00),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for refreeSystemTask */
osThreadId_t refreeSystemTaskHandle;
uint32_t MyBuffer_refree_task[ 128 ];
osStaticThreadDef_t MycontrolBloc_refree_task;
const osThreadAttr_t refreeSystemTask_attributes = {
  .name = "refreeSystemTask",
  .stack_mem = &MyBuffer_refree_task[0],
  .stack_size = sizeof(MyBuffer_refree_task),
  .cb_mem = &MycontrolBloc_refree_task,
  .cb_size = sizeof(MycontrolBloc_refree_task),
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for motor_init_task */
osThreadId_t motor_init_taskHandle;
uint32_t MyBufferTask04[ 128 ];
osStaticThreadDef_t MycontrolBlocTask04;
const osThreadAttr_t motor_init_task_attributes = {
  .name = "motor_init_task",
  .stack_mem = &MyBufferTask04[0],
  .stack_size = sizeof(MyBufferTask04),
  .cb_mem = &MycontrolBlocTask04,
  .cb_size = sizeof(MycontrolBlocTask04),
  .priority = (osPriority_t) osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of refreeSystemTask */
  refreeSystemTaskHandle = osThreadNew(refreeSystemTask, NULL, &refreeSystemTask_attributes);

  /* creation of motor_init_task */
  motor_init_taskHandle = osThreadNew(motor_init_task, NULL, &motor_init_task_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
	
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}
/* USER CODE BEGIN Header_StartDefaultTask */
/**
* @brief Function implementing the defaultTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN defaultTask */
  /* Infinite loop */
  for(;;)
  {
	static uint8_t pump_control = 0;
		
	static int crr = 100;
	static uint16_t adc;
	static uint32_t cnt = 0;
		__HAL_TIM_SET_COMPARE(&htim16, TIM_CHANNEL_1, crr);//crr���½�Ϊ70���£�-120���ϣ�
		adc = HAL_ADC_GetValue(&hadc1);
		
		cnt++;
		if(cnt%1000 == 0)
		{
			HAL_GPIO_TogglePin(motor_control_GPIO_Port,motor_control_Pin);
			HAL_GPIO_TogglePin(pump_control_GPIO_Port,pump_control_Pin);
		}
    osDelay(1);
  }
  /* USER CODE END defaultTask */
}

/* USER CODE BEGIN Header_refreeSystemTask */
/**
* @brief Function implementing the refreeSystemTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_refreeSystemTask */
void refreeSystemTask(void *argument)
{
  /* USER CODE BEGIN refreeSystemTask */
  /* Infinite loop */
while(1)
{
	if((camera_uart_buffer.write-camera_uart_buffer.read+Uart_Buffer_Len)%Uart_Buffer_Len >(uint16_t)(0.4*Uart_Buffer_Len))
	{
		//处理摄像头数据		
		
		for(;(camera_uart_buffer.write-camera_uart_buffer.read+Uart_Buffer_Len)%Uart_Buffer_Len>4;camera_uart_buffer.read = (camera_uart_buffer.read+1)%Uart_Buffer_Len )
		{
			if(find_Header())			//发现帧头
			{
				
				if((camera_uart_buffer.write-camera_uart_buffer.read+Uart_Buffer_Len)%Uart_Buffer_Len > camera_uart_buffer.buffer[camera_uart_buffer.read+4]+8)	//有效帧判别
				{
					objects_buffer.buffer[objects_buffer.write].object_num = (camera_uart_buffer.buffer[camera_uart_buffer.read+4]-4)/14;   //物体个数处理
					for(int i = 0;i<objects_buffer.buffer[objects_buffer.write].object_num;i++)  
					{
						objects_buffer.buffer[objects_buffer.write].obj[i].x_camera = camera_uart_buffer.buffer[camera_uart_buffer.read+10]+(camera_uart_buffer.buffer[camera_uart_buffer.read+11]<<8);
						objects_buffer.buffer[objects_buffer.write].obj[i].y_camera = camera_uart_buffer.buffer[camera_uart_buffer.read+12]+(camera_uart_buffer.buffer[camera_uart_buffer.read+13]<<8);
						objects_buffer.buffer[objects_buffer.write].obj[i].w_camera = camera_uart_buffer.buffer[camera_uart_buffer.read+14]+(camera_uart_buffer.buffer[camera_uart_buffer.read+15]<<8);
						objects_buffer.buffer[objects_buffer.write].obj[i].h_camera = camera_uart_buffer.buffer[camera_uart_buffer.read+16]+(camera_uart_buffer.buffer[camera_uart_buffer.read+17]<<8);
						objects_buffer.buffer[objects_buffer.write].obj[i].id = camera_uart_buffer.buffer[camera_uart_buffer.read+18]+(camera_uart_buffer.buffer[camera_uart_buffer.read+19]<<8);
						objects_buffer.buffer[objects_buffer.write].obj[i].confidence = (float)(camera_uart_buffer.buffer[camera_uart_buffer.read+20]+(camera_uart_buffer.buffer[camera_uart_buffer.read+21]<<8)+(camera_uart_buffer.buffer[camera_uart_buffer.read+22]<<16)+(camera_uart_buffer.buffer[camera_uart_buffer.read+23]<<24));
						
						
					}
					objects_buffer.write = (objects_buffer.write+1)%Objects_Buffer_Len;				//objects缓冲区取模自增
					//					if(objects_buffer.write ==  )				///缓冲区满业务逻辑
//					{}
				}
				else 
				{
					camera_uart_buffer.read = (camera_uart_buffer.read+1)%Uart_Buffer_Len;
					break;
				}
				
				
				
				
			}
			else
			{
				camera_uart_buffer.read = (camera_uart_buffer.read+1)%Uart_Buffer_Len;
				break;
			}
			
			
		}
		

		 
		
	}
		
}
	
  /* USER CODE END refreeSystemTask */
}

/* USER CODE BEGIN Header_motor_init_task */
/**
* @brief Function implementing the motor_init_task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_motor_init_task */
void motor_init_task(void *argument)
{
  /* USER CODE BEGIN motor_init_task */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END motor_init_task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

