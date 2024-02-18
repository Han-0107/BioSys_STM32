#include "lv_port_disp.h"
#include "lcd.h"
#include "ltdc.h"


//��������
#define LTDC_LCD_FRAMEBUF_SIZE		(1280*800*2)		//ltdc.c��ltdc_lcd_framebuf�������Ĵ�С
#define COLOR_BUF_SIZE		(LV_HOR_RES_MAX*LV_VER_RES_MAX)	//ȫ���Ĵ�С
static lv_color_t color_buf[COLOR_BUF_SIZE]	__attribute__((at(LCD_FRAME_BUF_ADDR+LTDC_LCD_FRAMEBUF_SIZE))); //���䵽�ⲿSDRAM,��Ҫ����ltdc.c�з����֡������
static lv_color_t color_buf2[COLOR_BUF_SIZE]	__attribute__((at(LCD_FRAME_BUF_ADDR+LTDC_LCD_FRAMEBUF_SIZE+COLOR_BUF_SIZE*2)));//lvgl�ĵڶ���������,�����ڵ�һ���������ĺ���
//��������
static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p);
#if LV_USE_GPU
static void gpu_blend(lv_color_t * dest, const lv_color_t * src, uint32_t length, lv_opa_t opa);
static void gpu_fill(lv_color_t * dest, uint32_t length, lv_color_t color);
#endif



//lvgl��ʾ�ӿڳ�ʼ��
void lv_port_disp_init(void)
{
	static lv_disp_buf_t disp_buf;
	
	//��ʾ��������ʼ��
	//��Ϊ�ⲿ��SDRAM�Ƚϴ�,�������ǿ�������Ϊ˫������
	lv_disp_buf_init(&disp_buf, color_buf, color_buf2, COLOR_BUF_SIZE); 

	//��ʾ����Ĭ��ֵ��ʼ��   
	lv_disp_drv_t disp_drv;                         
	lv_disp_drv_init(&disp_drv);                 

	//������Ļ����ʾ��С,��������Ϊ��֧������ԭ�ӵĶ����Ļ,���ö�̬��ȡ�ķ�ʽ
	//�����������ʵ����Ŀ�Ļ�,���Բ�������,��ô��Ĭ��ֵ����lv_conf.h��LV_HOR_RES_MAX��LV_VER_RES_MAX�궨���ֵ
	disp_drv.hor_res = lcddev.width;
	disp_drv.ver_res = lcddev.height;

	//ע����ʾ�����ص�
	disp_drv.flush_cb = disp_flush;

	//ע����ʾ������
	disp_drv.buffer = &disp_buf;

#if LV_USE_GPU
	//��ѡ��,ֻҪ��ʹ�õ�GPUʱ,����Ҫʵ��gpu_blend��gpu_fill�ӿ�

	//ʹ��͸���Ȼ��������ɫ����ʱ��Ҫ�õ�gpu_blend�ӿ�
	disp_drv.gpu_blend = gpu_blend;

	//��һ����ɫ���һ���ڴ�����ʱ��Ҫ�õ�gpu_fill�ӿ�
	disp_drv.gpu_fill = gpu_fill;
#endif

	//ע����ʾ������lvgl��
	lv_disp_drv_register(&disp_drv);
}


//��ָ���������ʾ����������д�뵽��Ļ��,�����ʹ��DMA����������Ӳ���������ں�̨ȥ����������
//���������֮��,�����õ���lv_disp_flush_ready()
static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
{
	//��ָ���������ʾ����������д�뵽��Ļ
	LCD_Color_Fill(area->x1,area->y1,area->x2,area->y2,(u16*)color_p);
	//������õ���,֪ͨlvgl�����Ѿ�flushing���������
	lv_disp_flush_ready(disp_drv);
}




//��ѡ��
#if LV_USE_GPU

/* If your MCU has hardware accelerator (GPU) then you can use it to blend to memories using opacity
 * It can be used only in buffered mode (LV_VDB_SIZE != 0 in lv_conf.h)*/
static void gpu_blend(lv_disp_drv_t * disp_drv, lv_color_t * dest, const lv_color_t * src, uint32_t length, lv_opa_t opa)
{
    /*It's an example code which should be done by your GPU*/
    uint32_t i;
    for(i = 0; i < length; i++) {
        dest[i] = lv_color_mix(dest[i], src[i], opa);
    }
}

/* If your MCU has hardware accelerator (GPU) then you can use it to fill a memory with a color
 * It can be used only in buffered mode (LV_VDB_SIZE != 0 in lv_conf.h)*/
static void gpu_fill_cb(lv_disp_drv_t * disp_drv, lv_color_t * dest_buf, lv_coord_t dest_width,
                    const lv_area_t * fill_area, lv_color_t color);
{
    /*It's an example code which should be done by your GPU*/
    uint32_t x, y;
    dest_buf += dest_width * fill_area->y1; /*Go to the first line*/

    for(y = fill_area->y1; y < fill_area->y2; y++) {
        for(x = fill_area->x1; x < fill_area->x2; x++) {
            dest_buf[x] = color;
        }
        dest_buf+=dest_width;    /*Go to the next line*/
    }
}

#endif 


