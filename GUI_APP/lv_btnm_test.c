#include "lv_btnm_test.h"
#include "lvgl.h"
#include "key.h"
#include <stdio.h>
#include "led.h"
#include "io.h"
#include "rs485.h"

lv_obj_t * btnm1;
lv_obj_t * label1;
lv_style_t bg_style;

//第二个const表示把此映射表放在flash存储区,而不是sram,可以减少内存的开销
static const char * const btnm1_map[] = {//btnm1的按钮映射表
"LED0","LED1","IO0","IO1","\n",		//每行放4个按钮，\n换行
"CMD1","btn6","btn7","btn8","\n",
"btn9","btn10","btn11","btn12","\n",
"btn13","btn14","btn15","btn16",""};//空字符串作为结束符

const lv_btnm_ctrl_t btnm1_ctrl_map[] = {//一一对应按键属性
//    2 | LV_BTNM_CTRL_INACTIVE,												 //禁用按键
//    1 | LV_BTNM_CTRL_NO_REPEAT,											   //不重复触发
//    LV_BTNM_CTRL_TGL_ENABLE | LV_BTNM_CTRL_TGL_STATE,	 //使能按键toggel状态
//    LV_BTNM_CTRL_CLICK_TRIG | LV_BTNM_CTRL_NO_REPEAT,  //松手后触发
	
		LV_BTNM_CTRL_TGL_ENABLE,
    LV_BTNM_CTRL_TGL_ENABLE,
		LV_BTNM_CTRL_TGL_ENABLE,
		LV_BTNM_CTRL_TGL_ENABLE,
    LV_BTNM_CTRL_NO_REPEAT,
    LV_BTNM_CTRL_NO_REPEAT,
    LV_BTNM_CTRL_NO_REPEAT,
    LV_BTNM_CTRL_NO_REPEAT,
    LV_BTNM_CTRL_NO_REPEAT,
    LV_BTNM_CTRL_NO_REPEAT,
    LV_BTNM_CTRL_NO_REPEAT,
		LV_BTNM_CTRL_NO_REPEAT,
		LV_BTNM_CTRL_NO_REPEAT,
    LV_BTNM_CTRL_NO_REPEAT,
    LV_BTNM_CTRL_NO_REPEAT,
		LV_BTNM_CTRL_NO_REPEAT    
};

char buff[100];
const char * btn_title;
uint16_t btn_id;
const uint8_t cmd1[8] = {0x01,0x06,0x00,0x02,0x00,0x03,0x68,0x0B};

//事件回调函数
static void event_handler(lv_obj_t * obj,lv_event_t event)
{
    if(obj == btnm1)
    {
        if(event == LV_EVENT_VALUE_CHANGED)
        {														
					//获取当前被点击了的按钮标题
						btn_title = lv_btnm_get_active_btn_text(btnm1);
						//获取当前被点击了的按钮id
						btn_id = lv_btnm_get_active_btn(btnm1);
					//把事件信息显示在标签上
					if(btn_id<16){
						sprintf(buff,"btn_id: %d\nbtn_title: %s",btn_id,btn_title);
						lv_label_set_text(label1,buff);
						printf("btn_id:%d\r\n",btn_id);				
					}	
						switch(btn_id)
						{
								case 0: LED0_Toggle;break;
								case 1: LED1_Toggle;break;
								case 2: IO_0_TOGGLE;break;
								case 3: IO_1_TOGGLE;break;
								case 4: 
									RS485_Send_Data((u8 *)cmd1,sizeof(cmd1));//发送cmd1		
									break;
								case 5: break;
								case 6: break;
								case 7: break;
								case 8: break;
								case 9: break;
								case 10: break;
								case 11: break;
								case 12: break;
								case 13: break;
								case 14: break;
								case 15: break;
								default: break;
						}
        }
    }
}


//例程入口
void lv_btnm_test_start()
{
    lv_obj_t * scr = lv_scr_act();
	
	  //1.使用night主题,当然了,你也可以换成其他的主题
//		lv_theme_t * theme = lv_theme_alien_init(210,NULL);//创建主题
//	lv_theme_t * theme = lv_theme_nemo_init(50,NULL);//创建主题
//		lv_theme_set_current(theme);//使用主题

		//1.创建一个自定义样式,用于修饰lv_btnm的背景
		lv_style_copy(&bg_style,&lv_style_pretty);
		bg_style.body.padding.top = 15;//上内边距
		bg_style.body.padding.bottom = 15;//底内边距
		bg_style.body.padding.left = 20;//左内边距
		bg_style.body.padding.right = 20;//右内边距
		bg_style.body.padding.inner = 15;//按钮与按钮之间的距离
	
		//2.创建一个类似于主菜单效果的btnm1
    btnm1 = lv_btnm_create(scr,NULL);
	  lv_obj_set_size(btnm1,400,400);//设置大小
    lv_obj_align(btnm1,NULL,LV_ALIGN_IN_TOP_MID,0,100);
    lv_btnm_set_map(btnm1,(const char**)btnm1_map);

	  lv_btnm_set_ctrl_map(btnm1,btnm1_ctrl_map);
//    lv_btnm_set_btn_ctrl(btnm1,0,LV_BTNM_CTRL_TGL_ENABLE | LV_BTNM_CTRL_TGL_STATE);
//	  lv_btnm_set_btn_ctrl_all(btnm1,LV_BTNM_CTRL_NO_REPEAT);
		lv_btnm_set_style(btnm1,LV_BTNM_STYLE_BG,&bg_style);//设置背景样式
    lv_obj_set_event_cb(btnm1,event_handler);
		
		//3.创建一个label标签用来显示信息
		label1 = lv_label_create(scr,NULL);
		lv_label_set_long_mode(label1,LV_LABEL_LONG_BREAK);//设置长文本模式
		lv_obj_set_width(label1,220);//设置宽度
		lv_obj_align(label1,btnm1,LV_ALIGN_OUT_BOTTOM_MID,0,10);//设置与btnm2的对齐方式
		lv_label_set_body_draw(label1,true);//使能背景绘制
		lv_label_set_recolor(label1,true);//使能文本重绘色
		lv_label_set_style(label1,LV_LABEL_STYLE_MAIN,&lv_style_plain_color);//设置背景
		lv_label_set_text(label1,"Event info");
}


