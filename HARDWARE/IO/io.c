#include "io.h"

//IO��ʼ��
void IO_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOH_CLK_ENABLE();			//����GPIOHʱ��

    GPIO_Initure.Pin=GPIO_PIN_2 | GPIO_PIN_3; //PH2,3
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //�������
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
    HAL_GPIO_Init(GPIOH,&GPIO_Initure);
	
		IO_0_HIGH;
		IO_1_HIGH;
}
