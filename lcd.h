#ifndef	__LCD_H__
#define	__LCD_H__

#include "type.h"

#define	LCD_HIGH 	(272)
#define	LCD_WIDTH	(480)

#define	 PICADD ((char *)0x140000)
#define	 PIC1 	((char *)0x80000)
#define	 PIC2 	((char *)0xC0000) 
#define	 PIC3 	((char *)0x100000)
#define		ENBASE		((en_word_t*)0x1C0000)
#define		CNBASE		((cn_word_t*)0x180000)
#define  PICBASE1   ((char *)0x31000000) //图片1的位置



//RGB565颜色设置方式
#define RGB565(r,g,b)		(((r & 0x1f) << 11) | ((g & 0x3f) << 5) | ((b & 0x1f) << 0))

#define   BLACK     RGB565(0,0,0)      //黑色    
#define   NAVY      RGB565(0,0,50)    //深蓝色
#define   PINK      RGB565(255, 128, 255)  //粉色
#define   BGCOLOR   RGB565(238, 120, 23)
#define   DGREEN    RGB565(0,50,0)    //深绿色  
#define   DCYAN     RGB565(0,127,127)  //深青色       
#define   MAROON    RGB565(50,0,0)    //深红色   
#define   GREEN     RGB565(0,255,0)    //绿色    
#define   RED       RGB565(255,0,0)    //红色     
#define   PURPLE    RGB565(127,0,127)  //紫色    
#define   OLIVE     RGB565(127,127,0)  //橄榄绿
#define   CGRAY     RGB565(240,240,240)///灰白色
#define   LGRAY     RGB565(88,88,88)///灰白色   
#define   DGRAY     RGB565(30,30,30)///浅紫色      
#define   BLUE      RGB565(0,0,255)    ///蓝色        
#define   CYAN      RGB565(0,255,255)  ///青色     
#define   MAGENTA   RGB565(255,0,255)  ///品红        
#define   YELLOW    RGB565(255,255,0)  ///黄色   
#define   WHITE     RGB565(255,255,255)///白色 


void ptr(char picture[]);   

 /****************************************
* 函数名：void lcd_init(void);
* 函数功能：
* 函数参数：
* 函数返回值;
* 修改时间：
*****************************************/
void lcd_init(void);

 /****************************************
* 函数名：void lcd_deinit(void);
* 函数功能：
* 函数参数：
* 函数返回值;
* 修改时间：
*****************************************/
void lcd_deinit(void);


/***************************************************************
函数名：void lcd_clean(int x,int y,int w,int h,rgb_t color)；
函数功能：把屏幕的任意大小的一块区域清成“color”颜色
函数参数：
@int x ：起始横坐标
@int y ：起始纵坐标
@int w ：宽	
@int h ：高
@rgb_t color：填充颜色
*******************************************************************/
void lcd_clean(int x,int y,int w,int h,rgb_t color);

/*********************************
 *函数名称：void LCD_setpixel(int x, int y, rgb_t color)
 *函数功能：打点
 *函数参数：
 *函数返回值：无
*********************************/
void lcd_setpixel(int x, int y, rgb_t color);

void lcd_showpic(int x,int y,int w,int h,char *pic);

void lcd_showpic2s(int x,int y,int w,int h,char *pic);

void lcd_showEn(int x,int y,char en,rgb_t fgcolor,rgb_t bgcolor);

void lcd_showCn(int x,int y,char cn[2],rgb_t fgcolor,rgb_t bgcolor);

void lcd_print(int x,int y,char *str,rgb_t fgcolor,rgb_t bgcolor);

void lcd_Swords(int x,int y,char *cn,rgb_t fgcolor,rgb_t bgcolor);

void LCD_SetBackGround(rgb_t color);

void lcd_newprint( unsigned x, unsigned y,char *string,rgb_t fgcolor,rgb_t bgcolor);

void lcd_myshowCn(int x,int y,char cn[2],rgb_t fgcolor);

void lcd_myshowEn(int x,int y,char en,rgb_t fgcolor);

void lcd_myprint(int x,int y,char *str,rgb_t fgcolo);

void lcd_print1(char *string, unsigned starX, unsigned starY, rgb_t bg_color, rgb_t font_color);

void LCD_SetPic(unsigned starX, unsigned starY, unsigned w, unsigned h, char *pic);

void LCD_SetPixel(unsigned x, unsigned y, rgb_t color);

void lcd_showEN(char en,int x,int y,rgb_t bgcolor,rgb_t fgcolor);

void lcd_showCN(char cn[2], int x, int y,rgb_t bgcolor, rgb_t fgcolor);

#endif

