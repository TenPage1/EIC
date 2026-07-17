//用于存储系统所需的变量



#include "stdint.h"

//	x坐标范围大约是0-62000，y坐标大约是0-112000
struct motor_42
{
	uint32_t target;
	uint32_t now;
	uint32_t speed;	//待开发
};
extern struct motor_42 m42_x,m42_y,m42_r;

struct screen{
	
	
	
};



#define Uart_Buffer_Len 256
struct UartBuffer//正在开发
{
	
	uint8_t buffer[Uart_Buffer_Len];
	uint16_t write;
	uint16_t read;
	

	uint8_t receive_data;
};
extern struct UartBuffer camera_uart_buffer;
void Uart1_Buffer_Init();


typedef uint8_t bool;
#define true  1
#define false 0
	
bool find_Header();


struct Object		//物体结构体   
{			
	uint16_t x_camera;
	uint16_t y_camera;
	uint16_t w_camera;
	uint16_t h_camera;
	uint32_t x_center;
	uint32_t y_center;
	uint16_t id;
	float confidence ; //置信度
	
};

#define Object_Len 10
struct Objects			//每帧数据包含物体结构体
{
	struct Object obj[Object_Len];
	uint8_t object_num;
};



#define Objects_Buffer_Len 20
struct Objects_Buffer
{
	struct Objects buffer[Objects_Buffer_Len];
	uint16_t write;
	uint16_t read;
};
extern struct Objects_Buffer objects_buffer;
void objects_buffer_Init();
//extern struct Objects objects;


struct Robot_Run
{
	uint8_t if_get_target ;
	uint8_t run_status;  ///0:不启动  1：获取目标物体 2：正在分拣
	struct Object target_object;
};
extern struct Robot_Run robot_run;
void Robot_Init();
//上电初始位置
#define Init_X 70000
#define Init_Y 90000
//坐标变换常数
//motor_y = Ky * camera_center_x + Dy
//motor_x = Kx * camera_cneter_y + Dx
#define Ky 730   
#define Kx 416
#define Dy -52210
#define Dx -11480