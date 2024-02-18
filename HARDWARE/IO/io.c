#include "io.h"

//IO初始化
void IO_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOH_CLK_ENABLE();			//开启GPIOH时钟

    GPIO_Initure.Pin=GPIO_PIN_2 | GPIO_PIN_3; //PH2,3
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
    HAL_GPIO_Init(GPIOH,&GPIO_Initure);
	
		IO_0_HIGH;
		IO_1_HIGH;
}
