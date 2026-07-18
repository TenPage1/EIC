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
#include "usart.h"
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
uint32_t MyBufferTask00[ 256 ];
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
uint32_t MyBuffer_refree_task[ 1280 ];
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
uint32_t MyBufferTask04[ 256 ];
osStaticThreadDef_t MycontrolBlocTask04;
const osThreadAttr_t motor_init_task_attributes = {
  .name = "motor_init_task",
  .stack_mem = &MyBufferTask04[0],
  .stack_size = sizeof(MyBufferTask04),
  .cb_mem = &MycontrolBlocTask04,
  .cb_size = sizeof(MycontrolBlocTask04),
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for Objects_Buffer_Task */
osThreadId_t Objects_Buffer_TaskHandle;
uint32_t MyBufferTask05[ 1280 ];
osStaticThreadDef_t MycontrolBlocTask05;
const osThreadAttr_t Objects_Buffer_Task_attributes = {
  .name = "Objects_Buffer_Task",
  .stack_mem = &MyBufferTask05[0],
  .stack_size = sizeof(MyBufferTask05),
  .cb_mem = &MycontrolBlocTask05,
  .cb_size = sizeof(MycontrolBlocTask05),
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for run_Task */
osThreadId_t run_TaskHandle;
uint32_t MyBufferTask06[ 1280 ];
osStaticThreadDef_t MycontrolBlocTask06;
const osThreadAttr_t run_Task_attributes = {
  .name = "run_Task",
  .stack_mem = &MyBufferTask06[0],
  .stack_size = sizeof(MyBufferTask06),
  .cb_mem = &MycontrolBlocTask06,
  .cb_size = sizeof(MycontrolBlocTask06),
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for Screen_Send_Task */
osThreadId_t Screen_Send_TaskHandle;
uint32_t MyBufferTask07[ 512 ];
osStaticThreadDef_t MycontrolBlocTask07;
const osThreadAttr_t Screen_Send_Task_attributes = {
  .name = "Screen_Send_Task",
  .stack_mem = &MyBufferTask07[0],
  .stack_size = sizeof(MyBufferTask07),
  .cb_mem = &MycontrolBlocTask07,
  .cb_size = sizeof(MycontrolBlocTask07),
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

  /* creation of Objects_Buffer_Task */
  Objects_Buffer_TaskHandle = osThreadNew(Objects_Buffer_Task, NULL, &Objects_Buffer_Task_attributes);

  /* creation of run_Task */
  run_TaskHandle = osThreadNew(run_Task, NULL, &run_Task_attributes);

  /* creation of Screen_Send_Task */
  Screen_Send_TaskHandle = osThreadNew(Screen_Send_Task, NULL, &Screen_Send_Task_attributes);

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
		
		//测试任务
	static uint8_t pump_control = 0;
		
	static int crr = 100;
	static uint16_t adc;
	static uint32_t cnt = 0;
		__HAL_TIM_SET_COMPARE(&htim16, TIM_CHANNEL_1, crr);//crr���½�Ϊ70���£�-120���ϣ�
		adc = HAL_ADC_GetValue(&hadc1);
		vTaskSuspend(defaultTaskHandle );
//		
//	char send_text[13] = "t1.txt=\"2\"";
//		send_text[10] = 0xFF;
//		send_text[11] = 0xFF;
//		send_text[12] = 0xFF;
//	HAL_UART_Transmit( &huart5, (uint8_t*)send_text, 13, 100);
//	osDelay(200);
	//	cnt++;
//		if(cnt%1000 == 0)
//		{
//			HAL_GPIO_TogglePin(motor_control_GPIO_Port,motor_control_Pin);
//			HAL_GPIO_TogglePin(pump_control_GPIO_Port,pump_control_Pin);
//		}
//    osDelay(1);
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
//osDelay(100);
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
					objects_buffer.buffer[objects_buffer.write].get_time = HAL_GetTick();
					for(int i = 0;i<objects_buffer.buffer[objects_buffer.write].object_num;i++)  
					{
						objects_buffer.buffer[objects_buffer.write].obj[i].x_camera = camera_uart_buffer.buffer[camera_uart_buffer.read+10]+(camera_uart_buffer.buffer[camera_uart_buffer.read+11]<<8);
						objects_buffer.buffer[objects_buffer.write].obj[i].y_camera = camera_uart_buffer.buffer[camera_uart_buffer.read+12]+(camera_uart_buffer.buffer[camera_uart_buffer.read+13]<<8);
						objects_buffer.buffer[objects_buffer.write].obj[i].w_camera = camera_uart_buffer.buffer[camera_uart_buffer.read+14]+(camera_uart_buffer.buffer[camera_uart_buffer.read+15]<<8);
						objects_buffer.buffer[objects_buffer.write].obj[i].h_camera = camera_uart_buffer.buffer[camera_uart_buffer.read+16]+(camera_uart_buffer.buffer[camera_uart_buffer.read+17]<<8);
						objects_buffer.buffer[objects_buffer.write].obj[i].id = camera_uart_buffer.buffer[camera_uart_buffer.read+18]+(camera_uart_buffer.buffer[camera_uart_buffer.read+19]<<8);
						
						if(objects_buffer.buffer[objects_buffer.write].obj[i].id == 6)			//将黄圆柱都改为黄圆锥
						{
							objects_buffer.buffer[objects_buffer.write].obj[i].id = 0;
						}
						
						objects_buffer.buffer[objects_buffer.write].obj[i].confidence = (float)(camera_uart_buffer.buffer[camera_uart_buffer.read+20]+(camera_uart_buffer.buffer[camera_uart_buffer.read+21]<<8)+(camera_uart_buffer.buffer[camera_uart_buffer.read+22]<<16)+(camera_uart_buffer.buffer[camera_uart_buffer.read+23]<<24));
						
						
							//进行xywh数据处理并计算得物体中心坐标
						objects_buffer.buffer[objects_buffer.write].obj[i].y_center = Ky * (objects_buffer.buffer[objects_buffer.write].obj[i].x_camera + objects_buffer.buffer[objects_buffer.write].obj[i].h_camera/2) + Dy;
						objects_buffer.buffer[objects_buffer.write].obj[i].x_center = Kx * (objects_buffer.buffer[objects_buffer.write].obj[i].y_camera + objects_buffer.buffer[objects_buffer.write].obj[i].w_camera/2) + Dx;
						objects_buffer.buffer[objects_buffer.write].get_time = HAL_GetTick();
						//盘内检验
						//正在开发
						if(objects_buffer.buffer[objects_buffer.write].obj[i].x_center < 0 || objects_buffer.buffer[objects_buffer.write].obj[i].y_center < 15000 || objects_buffer.buffer[objects_buffer.write].obj[i].x_center > 50000 || objects_buffer.buffer[objects_buffer.write].obj[i].y_center > 90000)							
						{
							objects_buffer.buffer[objects_buffer.write].object_num --;
							i--;
//							if(objects_buffer.buffer[objects_buffer.write].object_num == 0)
//							{
//								objects_buffer.write--;
//							}
						}
						
						
					}
					objects_buffer.write = (objects_buffer.write+1)%Objects_Buffer_Len;				//objects缓冲区取模自增
					
					
					//下级见Objects_Buffer_Task进行物体缓冲区的滤波和分拣业务处理

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
uint8_t x_button = 0;
uint8_t y_button = 0;
/* USER CODE END Header_motor_init_task */
void motor_init_task(void *argument)
{
  /* USER CODE BEGIN motor_init_task */
  /* Infinite loop */
  //测试不稳定
//	
//	m42_x.target = 100000;
//	m42_y.target = 120000;
//	while(1)
//	{
//		
//	//	static uint8_t x_button = 0;
//		static uint8_t finish = 0;
//		x_button = HAL_GPIO_ReadPin(x_button_GPIO_Port,x_button_Pin);
//		y_button = HAL_GPIO_ReadPin(y_button_GPIO_Port,y_button_Pin);
//		if(HAL_GPIO_ReadPin(x_button_GPIO_Port,x_button_Pin) == 0)
//		{
//			m42_x.now = Init_X;
//			m42_x.target = Init_X;
//			finish++;
//		
//		}
//		if(HAL_GPIO_ReadPin(y_button_GPIO_Port,y_button_Pin) == 0)
//		{
//			m42_y.now = Init_Y;
//			m42_y.target = Init_Y;
//			finish++;
//		}
//		if(finish == 2)
//		{
//			finish = 0;
//			vTaskSuspend(motor_init_taskHandle );
//			
//		}
//	}
//	
	//方案2：
	m42_x.now = Init_X;
	m42_x.target = Init_X;
	m42_y.now  = Init_Y;
	m42_y.target = Init_Y;
	
	vTaskSuspend(motor_init_taskHandle);
	
	
  /* USER CODE END motor_init_task */
}

/* USER CODE BEGIN Header_Objects_Buffer_Task */
/**
* @brief Function implementing the Objects_Buffer_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Objects_Buffer_Task */
void Objects_Buffer_Task(void *argument)
{
  /* USER CODE BEGIN Objects_Buffer_Task */
  /* Infinite loop */
//osDelay(100);
 while(1)
 {
		if(objects_buffer.buffer[(objects_buffer.write-1+Objects_Buffer_Len)%Objects_Buffer_Len].object_num != 0 && (HAL_GetTick()-objects_buffer.buffer[(objects_buffer.write-1+Objects_Buffer_Len)%Objects_Buffer_Len].get_time) <1000	)
		{
			robot_run.target_object = objects_buffer.buffer[(objects_buffer.write-1+Objects_Buffer_Len)%Objects_Buffer_Len].obj[0];
			robot_run.if_get_target = 1;
			
		}			
 }
	
  /* USER CODE END Objects_Buffer_Task */
}

/* USER CODE BEGIN Header_run_Task */
/**
* @brief Function implementing the run_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_run_Task */
void run_Task(void *argument)
{
  /* USER CODE BEGIN run_Task */
  /* Infinite loop */
 
  while(1)
	{
		static struct Object target_object ;
	  robot_run.if_get_target = 0;
		if(robot_run.run_status == 0 && robot_run.if_get_target == 1)
		{
			target_object = robot_run.target_object;
			
			
			robot_run.target_objects.objects[robot_run.target_objects.get_num] = target_object;			//压入已分拣序列
			robot_run.target_objects.get_num++;
			
			switch(robot_run.target_object.id)
			{
				case 0: case 6:
					m42_r.target = 0;
					break;
				case 1:
					m42_r.target = m42_r_60;
					break;
				case 2:
					m42_r.target = 2*m42_r_60;
					break;
				case 3:
					m42_r.target = 3*m42_r_60;
					break;
				case 4:
					m42_r.target = 4*m42_r_60;
					break;
				case 5:
					m42_r.target = 5*m42_r_60;
					break;
				
			}
			robot_run.run_status = 2;
			
			
			
			
		}
		if(robot_run.run_status == 2)
		{
			m42_x.target = target_object.x_center;
			m42_y.target = target_object.y_center;
			
			

			
			
			while(m42_x.target !=m42_x.now || m42_y.target !=m42_y.now)
			{
				osDelay(1);
			}
			__HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_1, 50);
			osDelay(200);
			HAL_GPIO_WritePin(pump_control_GPIO_Port,pump_control_Pin,1);
			osDelay(1000);
			m42_x.target = Init_X;
			m42_y.target = Init_Y-55000;
			__HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_1, 125);
			osDelay(100);
			while(m42_x.target !=m42_x.now || m42_y.target !=m42_y.now || m42_r.target !=m42_r.now)
			{
				osDelay(1);
			}
			HAL_GPIO_WritePin(pump_control_GPIO_Port,pump_control_Pin,0);		//松夹爪
			osDelay(100);
			
			
		char send_text[14] = "t10.txt=\"0\"";						//发送串口屏
		send_text[2]+=target_object.id;
		screen.id_cnt[target_object.id]++;
		send_text[9]=screen.id_cnt[target_object.id];
		send_text[11] = 0xFF;
		send_text[12] = 0xFF;
		send_text[13] = 0xFF;
		HAL_UART_Transmit( &huart5, (uint8_t*)send_text, 14, 10);
		osDelay(15);
		HAL_UART_Transmit( &huart5, (uint8_t*)send_text, 14, 10);
		osDelay(15);
		HAL_UART_Transmit( &huart5, (uint8_t*)send_text, 14, 10);
		osDelay(15);
			
			
		if(robot_run.run_status == 2)
		{robot_run.run_status = 0;}
			
			robot_run.if_get_target = 0;
		}
		if(robot_run.run_status == 3)	//复位模式
	{
		m42_x.target = Init_X;
		m42_x.target = Init_Y;
	}
	if(robot_run.run_status == 4)		//全手动模式
	{
		
	}
	}
  /* USER CODE END run_Task */
}

/* USER CODE BEGIN Header_Screen_Send_Task */
/**
* @brief Function implementing the Screen_Send_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Screen_Send_Task */
void Screen_Send_Task(void *argument)
{
  /* USER CODE BEGIN Screen_Send_Task */
  /* Infinite loop */
  for(;;)
  {
//		char send_text[14] = "t10.txt=\"0\"";
////		send_text[3]+=
//		send_text[11] = 0xFF;
//		send_text[12] = 0xFF;
//		send_text[13] = 0xFF;
//		HAL_UART_Transmit( &huart5, (uint8_t*)send_text, 14, 100);
//		osDelay(200);
  }
  /* USER CODE END Screen_Send_Task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

