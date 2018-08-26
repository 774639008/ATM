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
#define  PICBASE1   ((char *)0x31000000) //ͼƬ1��λ��



//RGB565��ɫ���÷�ʽ
#define RGB565(r,g,b)		(((r & 0x1f) << 11) | ((g & 0x3f) << 5) | ((b & 0x1f) << 0))

#define   BLACK     RGB565(0,0,0)      //��ɫ    
#define   NAVY      RGB565(0,0,50)    //����ɫ
#define   PINK      RGB565(255, 128, 255)  //��ɫ
#define   BGCOLOR   RGB565(238, 120, 23)
#define   DGREEN    RGB565(0,50,0)    //����ɫ  
#define   DCYAN     RGB565(0,127,127)  //����ɫ       
#define   MAROON    RGB565(50,0,0)    //���ɫ   
#define   GREEN     RGB565(0,255,0)    //��ɫ    
#define   RED       RGB565(255,0,0)    //��ɫ     
#define   PURPLE    RGB565(127,0,127)  //��ɫ    
#define   OLIVE     RGB565(127,127,0)  //�����
#define   CGRAY     RGB565(240,240,240)///�Ұ�ɫ
#define   LGRAY     RGB565(88,88,88)///�Ұ�ɫ   
#define   DGRAY     RGB565(30,30,30)///ǳ��ɫ      
#define   BLUE      RGB565(0,0,255)    ///��ɫ        
#define   CYAN      RGB565(0,255,255)  ///��ɫ     
#define   MAGENTA   RGB565(255,0,255)  ///Ʒ��        
#define   YELLOW    RGB565(255,255,0)  ///��ɫ   
#define   WHITE     RGB565(255,255,255)///��ɫ 


void ptr(char picture[]);   

 /****************************************
* ��������void lcd_init(void);
* �������ܣ�
* ����������
* ��������ֵ;
* �޸�ʱ�䣺
*****************************************/
void lcd_init(void);

 /****************************************
* ��������void lcd_deinit(void);
* �������ܣ�
* ����������
* ��������ֵ;
* �޸�ʱ�䣺
*****************************************/
void lcd_deinit(void);


/***************************************************************
��������void lcd_clean(int x,int y,int w,int h,rgb_t color)��
�������ܣ�����Ļ�������С��һ��������ɡ�color����ɫ
����������
@int x ����ʼ������
@int y ����ʼ������
@int w ����	
@int h ����
@rgb_t color�������ɫ
*******************************************************************/
void lcd_clean(int x,int y,int w,int h,rgb_t color);

/*********************************
 *�������ƣ�void LCD_setpixel(int x, int y, rgb_t color)
 *�������ܣ����
 *����������
 *��������ֵ����
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

