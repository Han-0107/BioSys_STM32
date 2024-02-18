#ifndef _IO_H
#define _IO_H
#include "sys.h"


/* 直接操作寄存器的方法控制*/
#define	digitalHi(p,i)			{p->BSRR=i;}			  //高电平		
#define digitalLo(p,i)			{p->BSRR=(uint32_t)i << 16;}	  //低电平
#define digitalToggle(p,i)		{p->ODR ^=i;}			  //反转

#define IO_0_Pin 				GPIO_PIN_2
#define IO_0_GPIO_Port 	GPIOH
#define IO_1_Pin 				GPIO_PIN_3
#define IO_1_GPIO_Port 	GPIOH

#define IO_0_HIGH					digitalHi(IO_0_GPIO_Port,IO_0_Pin)
#define IO_0_LOW				digitalLo(IO_0_GPIO_Port,IO_0_Pin)
#define IO_0_TOGGLE			digitalToggle(IO_0_GPIO_Port,IO_0_Pin)

#define IO_1_HIGH					digitalHi(IO_1_GPIO_Port,IO_1_Pin)
#define IO_1_LOW				digitalLo(IO_1_GPIO_Port,IO_1_Pin)
#define IO_1_TOGGLE			digitalToggle(IO_1_GPIO_Port,IO_1_Pin)

void IO_Init(void);
#endif
