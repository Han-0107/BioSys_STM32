#ifndef __GT9271_H
#define __GT9271_H	
#include "sys.h"	
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//10.1����ݴ�����-GT9271 ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2017/6/7
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 


//IO��������	 
#define GT9271_RST(n)  (n?HAL_GPIO_WritePin(GPIOI,GPIO_PIN_8,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOI,GPIO_PIN_8,GPIO_PIN_RESET))//GT9147��λ����
#define GT9271_INT      HAL_GPIO_ReadPin(GPIOH,GPIO_PIN_7)  //GT9147�ж�����		
 
//I2C��д����	
#define GT9271_CMD_WR 		0X28    	//д����
#define GT9271_CMD_RD 		0X29		//������
  
//GT9271 ���ּĴ������� 
#define GT9271_CTRL_REG 	0X8040   	//GT9271���ƼĴ���
#define GT9271_CFGS_REG 	0X8047   	//GT9271������ʼ��ַ�Ĵ���
#define GT9271_CHECK_REG 	0X80FF   	//GT9271У��ͼĴ���
#define GT9271_PID_REG 		0X8140   	//GT9271��ƷID�Ĵ���

#define GT9271_GSTID_REG 	0X814E   	//GT9271��ǰ��⵽�Ĵ������
#define GT9271_TP1_REG 		0X8150  	//��һ�����������ݵ�ַ
#define GT9271_TP2_REG 		0X8158		//�ڶ������������ݵ�ַ
#define GT9271_TP3_REG 		0X8160		//���������������ݵ�ַ
#define GT9271_TP4_REG 		0X8168		//���ĸ����������ݵ�ַ
#define GT9271_TP5_REG 		0X8170		//��������������ݵ�ַ 
#define GT9271_TP6_REG 		0X8178		//��������������ݵ�ַ 
#define GT9271_TP7_REG 		0X8180		//��������������ݵ�ַ 
#define GT9271_TP8_REG 		0X8188		//��������������ݵ�ַ 
#define GT9271_TP9_REG 		0X8190		//��������������ݵ�ַ 
#define GT9271_TP10_REG 	0X8198		//��������������ݵ�ַ  
 
 
u8 GT9271_Send_Cfg(u8 mode);
u8 GT9271_WR_Reg(u16 reg,u8 *buf,u8 len);
void GT9271_RD_Reg(u16 reg,u8 *buf,u8 len); 
u8 GT9271_Init(void);
u8 GT9271_Scan(u8 mode); 
#endif













