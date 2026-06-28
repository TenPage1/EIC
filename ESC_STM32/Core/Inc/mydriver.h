//用于存储整个系统所需的数据



#include "stdint.h"

//	
struct motor_42{
//	uint8_t direction;
	uint32_t target;
	uint32_t now;
};
extern struct motor_42 m42_x,m42_y,m42_r;
