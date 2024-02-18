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

//ע:����littleVGL��,��ò�Ҫ����-O���Ż�,����Ϊ-O0���Ż��Ϳ�����


int main(void)
{
	Cache_Enable();                 //��L1-Cache
	MPU_Memory_Protection();				//����ĳЩ�洢����,���ʹ���ⲿSDRAM�����ٵĻ�,�����õ���
	HAL_Init();				        			//��ʼ��HAL��
	Stm32_Clock_Init(432,25,2,9);   //����ʱ��,216Mhz 
	delay_init(216);                //��ʱ��ʼ��
	uart_init(115200);		        	//���ڳ�ʼ��
	LED_Init();                     //��ʼ��LED
	KEY_Init();                     //��ʼ������
	
	IO_Init();											//IO���Ƴ�ʼ��
		
	RS485_Init(9600);		        //��ʼ��RS485
	
	SDRAM_Init();                   //��ʼ��SDRAM
	TIM3_Init(999,107);							//��ʱ����ʼ��(1ms�ж�),���ڸ�lvgl�ṩ1ms����������
	LCD_Init();                     //LCD��ʼ��
	if(lcdltdc.pwidth!=0)		
		LCD_Display_Dir(1);						//�����RGB���Ļ�,��ǿ������Ϊ������ʾ
	tp_dev.init();				    			//��������ʼ�� 
  
	lv_init();											//lvglϵͳ��ʼ��
	lv_port_disp_init();						//lvgl��ʾ�ӿڳ�ʼ��,����lv_init()�ĺ���
	lv_port_indev_init();						//lvgl����ӿڳ�ʼ��,����lv_init()�ĺ���
	
	lv_btnm_test_start();						//��������
	
	while(1)
	{
		tp_dev.scan(0);//����ɨ��
		lv_task_handler();//lvgl��������
	}
}
