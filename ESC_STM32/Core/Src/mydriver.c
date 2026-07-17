#include "mydriver.h"



struct motor_42 m42_x,m42_y;



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


struct Objects_Buffer objects_buffer;
void objects_buffer_Init()
{
	objects_buffer.read = 0;
	objects_buffer.write = 0;
}