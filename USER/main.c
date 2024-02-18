#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "mpu.h"
#include "timer.h"
#include "lcd.h"
#include "ltdc.h"
#include "sdram.h"
#include "touch.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "lv_btnm_test.h" 
#include "io.h"
#include "rs485.h"

//注:对于littleVGL库,最好不要采用-O的优化,保持为-O0不优化就可以了


int main(void)
{
	Cache_Enable();                 //打开L1-Cache
	MPU_Memory_Protection();				//保护某些存储区域,如果使用外部SDRAM来加速的话,则必须得调用
	HAL_Init();				        			//初始化HAL库
	Stm32_Clock_Init(432,25,2,9);   //设置时钟,216Mhz 
	delay_init(216);                //延时初始化
	uart_init(115200);		        	//串口初始化
	LED_Init();                     //初始化LED
	KEY_Init();                     //初始化按键
	
	IO_Init();											//IO控制初始化
		
	RS485_Init(9600);		        //初始化RS485
	
	SDRAM_Init();                   //初始化SDRAM
	TIM3_Init(999,107);							//定时器初始化(1ms中断),用于给lvgl提供1ms的心跳节拍
	LCD_Init();                     //LCD初始化
	if(lcdltdc.pwidth!=0)		
		LCD_Display_Dir(1);						//如果是RGB屏的话,则强制设置为横屏显示
	tp_dev.init();				    			//触摸屏初始化 
  
	lv_init();											//lvgl系统初始化
	lv_port_disp_init();						//lvgl显示接口初始化,放在lv_init()的后面
	lv_port_indev_init();						//lvgl输入接口初始化,放在lv_init()的后面
	
	lv_btnm_test_start();						//运行例程
	
	while(1)
	{
		tp_dev.scan(0);//触摸扫描
		lv_task_handler();//lvgl的事务处理
	}
}
