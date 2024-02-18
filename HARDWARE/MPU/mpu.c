#include "mpu.h"
#include "led.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F7������
//MPU��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/11/30
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 

//����ĳ�������MPU����
//baseaddr:MPU��������Ļ�ַ(�׵�ַ)
//size:MPU��������Ĵ�С(������32�ı���,��λΪ�ֽ�),�����õ�ֵ�ο�:CORTEX_MPU_Region_Size
//rnum:MPU���������,��Χ:0~7,���֧��8����������,�����õ�ֵ�ο���CORTEX_MPU_Region_Number
//ap:����Ȩ��,���ʹ�ϵ����:�����õ�ֵ�ο���CORTEX_MPU_Region_Permission_Attributes
//MPU_REGION_NO_ACCESS,�޷��ʣ���Ȩ&�û������ɷ��ʣ�
//MPU_REGION_PRIV_RW,��֧����Ȩ��д����
//MPU_REGION_PRIV_RW_URO,��ֹ�û�д���ʣ���Ȩ�ɶ�д���ʣ�
//MPU_REGION_FULL_ACCESS,ȫ���ʣ���Ȩ&�û����ɷ��ʣ�
//MPU_REGION_PRIV_RO,��֧����Ȩ������
//MPU_REGION_PRIV_RO_URO,ֻ������Ȩ&�û���������д��
//���:STM32F7 Series Cortex-M7 processor programming manual.pdf,4.6��,Table 89.
//����ֵ;0,�ɹ�.
//    ����,����.
u8 MPU_Set_Protection(u32 baseaddr,u32 size,u32 rnum,u32 ap)
{
	MPU_Region_InitTypeDef MPU_Initure;
	
	HAL_MPU_Disable();								        //����MPU֮ǰ�ȹر�MPU,��������Ժ���ʹ��MPU

	MPU_Initure.Enable=MPU_REGION_ENABLE;			        //ʹ�ܸñ������� 
	MPU_Initure.Number=rnum;			                    //���ñ�������
	MPU_Initure.BaseAddress=baseaddr;	                    //���û�ַ
	MPU_Initure.Size=size;				                    //���ñ��������С
	MPU_Initure.SubRegionDisable=0X00;                      //��ֹ������
	MPU_Initure.TypeExtField=MPU_TEX_LEVEL0;                //����������չ��Ϊlevel0
	MPU_Initure.AccessPermission=(u8)ap;		            //���÷���Ȩ��,
	MPU_Initure.DisableExec=MPU_INSTRUCTION_ACCESS_ENABLE;	//����ָ�����(�����ȡָ��)
	MPU_Initure.IsShareable=MPU_ACCESS_NOT_SHAREABLE;       //��ֹ����
	MPU_Initure.IsCacheable=MPU_ACCESS_CACHEABLE;       //����cache  
	MPU_Initure.IsBufferable=MPU_ACCESS_BUFFERABLE;         //������
	HAL_MPU_ConfigRegion(&MPU_Initure);                     //����MPU
	HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);			        //����MPU
    return 0;
}

//������Ҫ�����Ĵ洢��
//����Բ��ִ洢�������MPU����,������ܵ��³��������쳣
//����MCU������ʾ,����ͷ�ɼ����ݳ���ȵ�����...
void MPU_Memory_Protection(void)
{
	MPU_Set_Protection(0x60000000,MPU_REGION_SIZE_64MB,MPU_REGION_NUMBER0,MPU_REGION_FULL_ACCESS);	//����MCU LCD�����ڵ�FMC����,,��64M�ֽ�
	MPU_Set_Protection(0x20000000,MPU_REGION_SIZE_512KB,MPU_REGION_NUMBER1,MPU_REGION_FULL_ACCESS);		//���������ڲ�SRAM,����SRAM1,SRAM2��DTCM,��512K�ֽ�
	MPU_Set_Protection(0XC0000000,MPU_REGION_SIZE_32MB,MPU_REGION_NUMBER2,MPU_REGION_FULL_ACCESS);	//����SDRAM����,��32M�ֽ�
	MPU_Set_Protection(0X80000000,MPU_REGION_SIZE_256MB,MPU_REGION_NUMBER3,MPU_REGION_FULL_ACCESS);	//��������NAND FLASH����,��256M�ֽ�
}

//MemManage�������ж�
//������ж��Ժ�,���޷��ָ���������!!
void MemManage_Handler(void)
{ 
	LED1(0);							//����DS1
	printf("Mem Access Error!!\r\n"); 	//���������Ϣ
	delay_ms(1000);	
	printf("Soft Reseting...\r\n");		//��ʾ�������
	delay_ms(1000);	
	NVIC_SystemReset();					//��λ
}
