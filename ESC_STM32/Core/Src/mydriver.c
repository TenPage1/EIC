#include "mydriver.h"



struct motor_42 m42_x,m42_y,m42_r;



struct UartBuffer camera_uart_buffer;			//摄像头uart缓冲区结构体
void Uart1_Buffer_Init()			//摄像头Uart缓冲区结构体使能
{
	camera_uart_buffer.read = 0;
	camera_uart_buffer.write = 0;
	for(int i ;i<Uart_Buffer_Len;i++)
	{
		camera_uart_buffer.buffer[i] = 0;
	}
	
}

bool find_Header()					//检验当前位是否位于帧头，用于摄像头Uart缓冲区处理
{
	if(camera_uart_buffer.buffer[camera_uart_buffer.read] == 0xAA && camera_uart_buffer.buffer[(camera_uart_buffer.read+1)%Uart_Buffer_Len] == 0xCA && camera_uart_buffer.buffer[(camera_uart_buffer.read+2)%Uart_Buffer_Len] == 0xAC && camera_uart_buffer.buffer[(camera_uart_buffer.read+3)%Uart_Buffer_Len] == 0xBB)
	{
		return true;
	}
	else 
	{
		return false;
	}
}



struct Objects_Buffer objects_buffer;			//物体缓冲区结构体
void objects_buffer_Init()
{
	objects_buffer.read = 0;
	objects_buffer.write = 0;
}


struct Robot_Run robot_run;
void Robot_Init()
{
	robot_run.if_get_target = 0;
	robot_run.run_status = 0;
	robot_run.target_objects.get_num = 0;
	
}


struct Screen	screen ;		//串口屏结构体
void screen_Init()
{
	for(int i = 0;i<ID_NUM;i++)
	{
		screen.id_cnt[i] = '0';
	}

}