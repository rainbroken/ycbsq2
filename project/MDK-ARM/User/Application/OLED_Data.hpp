#pragma once

#include <stdint.h>

typedef uint8_t u8;
typedef uint16_t u16;

/*中文字符字节宽度*/
#define OLED_CHN_CHAR_WIDTH			3		//UTF-8编码格式给3，GB2312编码格式给2

/*字模基本单元*/
typedef struct 
{
	char Index[OLED_CHN_CHAR_WIDTH + 1];	//汉字索引
	uint8_t Data[32];						//字模数据
} ChineseCell_t;

/*ASCII字模数据声明*/
extern const uint8_t OLED_F8x16[][16];
extern const uint8_t OLED_F6x8[][6];

/*汉字字模数据声明*/
extern const ChineseCell_t OLED_CF16x16[];
extern const uint8_t OLED_NUM[][64];
/*图像数据声明*/
extern const uint8_t Diode[];
/*按照上面的格式，在这个位置加入新的图像数据声明*/

extern const uint8_t goutou[];

extern const uint8_t Wallpaper[];
//...
	


/*****************江协科技|版权所有****************/
/*****************jiangxiekeji.com*****************/
