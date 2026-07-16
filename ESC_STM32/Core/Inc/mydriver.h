//用于存储整个系统所需的数据



#include "stdint.h"

//	x坐标范围大约是0-62000，y坐标大约是0-112000
struct motor_42{
//	uint8_t direction;
	uint32_t target;
	uint32_t now;
	uint32_t speed;	//待开发
};
extern struct motor_42 m42_x,m42_y,m42_r;
struct screen{
	
	
	
};
struct camera_uart_buffer//没想好
{
	uint8_t buffer[20];
	
};