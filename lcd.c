#include <s3c2440.h>
#include <string.h>
#include "lcd.h"
#include "type.h"

//1.LCDCON1的控制寄存器参数
#define CLKVAL	(4 << 8)	//设置公式:VCLK=HCLK / [(CLKVAL + 1) × 2]	(CLKVAL≥0)
#define MMODE		(0 << 7)	//VM触发频率，TFT不用，设置为0
#define	PNRMODE	(3 << 5)	//显示模式 TFT 11
#define	BEEMODE (12 << 1)	//像素点位数，TFT  16位模式：1100
#define	ENVID 	(0 << 0)	//控制视频输出，也就是EN位，先默认关闭
#define LCDCON_VAL1	(CLKVAL | MMODE | PNRMODE | BEEMODE | ENVID)

//2.LCDCON2
#define	VBPD		(2 << 24)	//垂直同步信号周期后无效的行数
#define	LINEVAL	((LCD_HIGH-1) << 14)	//LCD的垂直尺寸（高度）
#define	VFPD		(2 << 6)		//垂直同步周期信号
#define	VSPW		(10 << 0)
#define LCDCON_VAL2	(VBPD | LINEVAL | VFPD | VSPW)

//LCDCON3
#define		HBPD		(2 << 19)
#define		HOZVAL	((LCD_WIDTH-1) << 8)
#define		HFPD		(2 << 0)
#define		LCDCON_VAL3	(HBPD | HOZVAL | HFPD)

//LCDCON4
#define		HSPW		(40 << 0)		//TYP=41标准再减1
#define		LCDCON_VAL4	HSPW

//LCDCON5
#define		BPP24BL		(0 << 12)
#define		FRM565		(1 << 11)
//时序图引脚翻转配置
#define		INVVCLK		(0x0 << 10)
#define		INVLINE		(0x1 << 9)
#define		INVFRAME	(0x1 << 8)
#define		INVVD			(0x0 << 7)
#define		INVVDEN		(0x1 << 6)
#define		INVPWREN	(0x0 << 5)
#define		INVLEND		(0x0 << 4)

#define 	PWREN			(0 << 3)
#define		ENLEND		(0 << 2)

#define 	BSWP		(0x0 << 1)
#define		HWSWP		(0x1 << 0)

#define 	LCDCON_VAL5	(BPP24BL | FRM565 | INVVCLK | INVLINE | \
												INVFRAME | INVVD | INVVDEN | INVPWREN | \
												INVLEND | PWREN | ENLEND | BSWP | HWSWP)

static volatile	rgb_t G_lcdBuffer[LCD_HIGH][LCD_WIDTH];

//LCD缓冲区，用来给数据
#define LCDBASE	((unsigned long)G_lcdBuffer)

//配置缓冲区地址
#define		LCDBANK		(((LCDBASE >>22) & 0x1FF) << 21)
#define		LCDBASEU	((LCDBASE >>1) & 0x1FFFFF << 0)
#define		vLCDADDR1	(LCDBANK | LCDBASEU)

#define		LCDBASEL		(((LCDBASE + LCD_WIDTH * LCD_HIGH * 2) >> 1) & 0x1FFFFF)
#define		vLCDADDR2		LCDBASEL

#define		OFFSIZE		0x0
#define		PAGEWIDTH (LCD_WIDTH)
#define		vLCDADDR3		(OFFSIZE | PAGEWIDTH)

//帧缓冲区 一帧的数据，所有的像素点，16位
typedef unsigned short RGB_COLOR;
volatile RGB_COLOR frameBuffer[LCD_HIGH][LCD_WIDTH];//列是宽，480


void ptr(char picture[])
{
	memcpy((char *)G_lcdBuffer,picture,480*272*2);
}



/****************************************
* 函数名：void lcd_init(void);
* 函数功能：
* 函数参数：
* 函数返回值;
* 修改时间：
*****************************************/
void lcd_init()
{
	//1.配置引脚
	GPCCON = 0xAAAAFEAB;
	GPDCON = 0xAAAAAAAA;
	GPGCON |= (0x3 << 8); 
	
	//2.配置寄存器，控制寄存器
	LCDCON1 =LCDCON_VAL1;
	LCDCON2 =LCDCON_VAL2;
	LCDCON3 =LCDCON_VAL3;
	LCDCON4 =LCDCON_VAL4;
	LCDCON5 =LCDCON_VAL5;
	
	//3.配置缓冲区地址
	LCDSADDR1 = vLCDADDR1;
	LCDSADDR2 = vLCDADDR2;
	LCDSADDR3 = vLCDADDR3;
	
	//4.打开LCD的电源
	BIT_SET(LCDCON5,3);
	BIT_SET(LCDCON1,0);
	
	memset((void*)G_lcdBuffer,110,sizeof(G_lcdBuffer));
	lcd_clean(0,0,LCD_WIDTH,LCD_HIGH,BLUE);
}

 /****************************************
* 函数名：void lcd_deinit(void);
* 函数功能：
* 函数参数：
* 函数返回值;
* 修改时间：
*****************************************/
void lcd_deinit()
{}

/*********************************
 *函数名称：void LCD_setpixel(int x, int y, rgb_t color)
 *函数功能：打点
 *函数参数：
 *函数返回值：无
*********************************/
void lcd_setpixel(int x, int y, rgb_t color)
{
	if(x < 0 || x >=LCD_WIDTH || y < 0 || y >= LCD_HIGH)
		return ;
	
	G_lcdBuffer[y][x] = color;
}
	
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
void lcd_clean(int x,int y,int w,int h,rgb_t color)
{
	int i;
	
	if(x < 0 || x >=LCD_WIDTH || y < 0 || y >= LCD_HIGH)
		return ;
	
	for(i = x; i < x+w; i++)
	{
		G_lcdBuffer[y][i] = color;
	}
	
	for(i = 1; i < h; i++)
	{
		memcpy((void*)&G_lcdBuffer[y+i][x], (void*)&G_lcdBuffer[y][x], w*sizeof(rgb_t));
	}
}

/***************************************************************
函数名：void lcd_showpic(int x,int y,int w,int h,char *pic)
函数功能：显示一张烧在内存里面的图
函数参数：
@int x ：起始横坐标
@int y ：起始纵坐标
@int w ：宽	
@int h ：高
@char *pic：图片地址
*******************************************************************/
void lcd_showpic(int x,int y,int w,int h,char *pic)
{
	int i,j;
	rgb_t color;
	for(i=0;i<h;i++)
	{
		for(j=0;j<w;j++)
		{
			color = *pic | ((*(pic +1))<<8);
			lcd_setpixel(j+x,i+y,color);
			pic += 2;
		}		
	}
}

void lcd_showpic2s(int x,int y,int w,int h,char *pic)
{
	int i,j;
	rgb_t color;
	for(i=0;i<h;i++)
	{
		for(j=0;j<w;j++)
		{
			color = *pic | ((*(pic +1))<<8);
			lcd_setpixel(j+x,i+y,color);
			pic += 8;
		}
		pic += 480*4;		
	}
}

/***************************************************************
函数名：void lcd_showEn(int x,int y,char en,rgb_t fgcolor,rgb_t bgcolor)
函数功能：根据输入显示一个烧在内存中文字符
函数参数：
@int x ：起始横坐标
@int y ：起始纵坐标
@char en：要打印的英文字符
@rgb_t fgcolor：前景色即字符的颜色
@rgb_t bgcolor：背景色即字符背后的颜色
*******************************************************************/
void lcd_showEn(int x,int y,char en,rgb_t fgcolor,rgb_t bgcolor)
{
	int index = en -0x20;
	int i,j;
	for(i=0;i<16;i++)
	{
		for(j=0;j<8;j++)
		{
			if(ENBASE[index].data[i]&(1<<(7-j)))
				lcd_setpixel(x+j,y+i,fgcolor);
			else
				lcd_setpixel(x+j,y+i,bgcolor);
		}
	}
}

/***************************************************************
函数名：void lcd_showCn(int x,int y,char cn[2],rgb_t fgcolor,rgb_t bgcolor)
函数功能：根据输入显示一个烧在内存中文字符
函数参数：
@int x ：起始横坐标
@int y ：起始纵坐标
@char en[2]：要打印的中文文字符
@rgb_t fgcolor：前景色即字符的颜色
@rgb_t bgcolor：背景色即字符背后的颜色
*******************************************************************/
void lcd_showCn(int x,int y,char cn[2],rgb_t fgcolor,rgb_t bgcolor)
{
	int row = cn[0] - 0xA1;
	int col = cn[1] - 0xA1;
	cn_word_t pWord = CNBASE[row*94+col];//当前汉字的点阵数据
	int i,j;
	short word = (pWord.data[0]<<8)|pWord.data[1];
	
	for(i=0;i < 16;i++)
	{
		word = (pWord.data[i * 2]<<8)|pWord.data[i*2+1];
		for(j=0;j < 16;j++)
		{
			if(word&(1<<(15-j)))
			{
					lcd_setpixel(x+j,y+i,fgcolor);
			}
			else
				lcd_setpixel(x+j,y+i,bgcolor);
		}
	}	
}

/***************************************************************
函数名：void lcd_showCn(int x,int y,char cn[2],rgb_t fgcolor,rgb_t bgcolor)
函数功能：根据输入显示一个烧在内存中文字符
函数参数：
@int x ：起始横坐标
@int y ：起始纵坐标
@char en[128]：要打印的中英文字符串
@rgb_t fgcolor：前景色即字符的颜色
@rgb_t bgcolor：背景色即字符背后的颜色
*******************************************************************/
void lcd_Swords(int x,int y,char *cn,rgb_t fgcolor,rgb_t bgcolor)
{
	char word[2];
	int i;
	for(i=0;i<=128;i++)
	{
		word[0]=cn[i];
		if(word[0]==0)
		{
			break;
		}	
		if((int)word[0] > 0xA0)
		{
			i++;
			word[1]=cn[i];
			lcd_showCn(x+(i-1)*10,y,word,fgcolor,bgcolor);
			word[1]=0;
		}
		else
			lcd_showEn(x+i*10,y,word[0],fgcolor,bgcolor);
	}
}


void lcd_myshowCn(int x,int y,char cn[2],rgb_t fgcolor)
{
	int row = cn[0] - 0xA1;
	int col = cn[1] - 0xA1;
	cn_word_t pWord = CNBASE[row*94+col];//当前汉字的点阵数据
	int i,j;
	short word = (pWord.data[0]<<8)|pWord.data[1];
	
	for(i=0;i < 16;i++)
	{
		word = (pWord.data[i * 2]<<8)|pWord.data[i*2+1];
		for(j=0;j < 16;j++)
		{
			if(word&(1<<(15-j)))
			{
					lcd_setpixel(x+j,y+i,fgcolor);
			}
		}
	}	
}

void lcd_myshowEn(int x,int y,char en,rgb_t fgcolor)
{
	int index = en -0x20;
	int i,j;
	for(i=0;i<16;i++)
	{
		for(j=0;j<8;j++)
		{
			if(ENBASE[index].data[i]&(1<<(7-j)))
				lcd_setpixel(x+j,y+i,fgcolor);
		}
	}
}


void lcd_print(int x,int y,char *str,rgb_t fgcolor,rgb_t bgcolor)
{
	int pos = 0;
	while(*str != '\0')
	{
		if(*str & 0x80)
		{
			lcd_showCn(x+pos*18,y,str,fgcolor,bgcolor);
			str += 2;
		}
		else
		{
			
			lcd_showEn(x+pos*9,y,*str,fgcolor,bgcolor);
			str++;
		}
		pos++;
	}

}
/**
 * 函数名：LCD_SetBackGround
 * 作用：打印背景颜色
 * 参数：
 * 		@color: 打印的颜色
 */   
void LCD_SetBackGround(rgb_t color)
{
	int i, j;
	for(j = 0; j < LCD_WIDTH; j++)
	{
		G_lcdBuffer[0][j] = color;
	}
	for(i = 1; i < LCD_HIGH; i++)
	{
		memcpy((void *)(G_lcdBuffer+i), (void *)G_lcdBuffer, sizeof(G_lcdBuffer)/LCD_HIGH);
	}

}

void lcd_newprint( unsigned x, unsigned y,char *string,rgb_t fgcolor,rgb_t bgcolor)
{
	unsigned i, len = strlen(string);
	for(i = 0; i < len;)
	{
		if((unsigned)string[i] < 0x80)
		{
			lcd_showEn(x + i*8, y,string[i], fgcolor,  bgcolor);
			i++;
		}
		else
		{
			lcd_showCn( x + i*8, y,string+i, fgcolor,  bgcolor);
			i += 2;
		}
	}
}




void lcd_myprint(int x,int y,char *str,rgb_t fgcolor)
{
	int pos = 0;
	while(*str != '\0')
	{
		if(*str & 0x80)
		{
			lcd_myshowCn(x+pos*18,y,str,fgcolor);
			str += 2;
		}
		else
		{
			
			lcd_myshowEn(x+pos*9,y,*str,fgcolor);
			str++;
		}
		pos++;
	}

}




/*
 * 函数名：Print_Bmp
 * 作用：快速打印背景图片
 * 参数：
 *    @pic
 */
void Print_Bmp(const char *pic)
{
	memcpy((void *)frameBuffer, (void *)pic, sizeof(frameBuffer));
}


void lcd_showCN(char cn[2], int x, int y,rgb_t bgcolor, rgb_t fgcolor)
{
	int row = cn[0] - 0xA1;
	int col = cn[1] - 0xA1;
	cn_word_t pWord = CNBASE[row*94+col];//当前汉字的点阵数据
	int i,j;
	short word = (pWord.data[0]<<8)|pWord.data[1];
	
	for(i=0;i < 16;i++)
	{
		word = (pWord.data[i * 2]<<8)|pWord.data[i*2+1];
		for(j=0;j < 16;j++)
		{
			if(word&(1<<(15-j)))
			{
				lcd_setpixel(x+j,y+i,fgcolor);
			}
			else
				lcd_setpixel(x+j,y+i,bgcolor);
		}
	}	
}
/*7*
 * 函数名：lcd_showEN
 * 作用：打印一个英文字符
 * 参数：
 * 		@en：所要打印的字符
 * 		@starX: 英文字符的起始点横坐标
 *		@starY: 英文字符的起始点纵坐标
 * 		@font_color：前景色
 * 		@bg_color: 背景色
 */
void lcd_showEN(char en,int x,int y,rgb_t bgcolor,rgb_t fgcolor)
{
	int index = en -0x20;
	int i,j;
	for(i=0;i<16;i++)
	{
		for(j=0;j<8;j++)
		{
			if(ENBASE[index].data[i]&(1<<(7-j)))
				lcd_setpixel(x+j,y+i,fgcolor);
			else
				lcd_setpixel(x+j,y+i,bgcolor);
		}
	}
}

void lcd_print1(char *string, unsigned starX, unsigned starY, rgb_t bg_color, rgb_t font_color)
{
	unsigned i, len = strlen(string);
	for(i = 0; i < len;)
	{
		if((unsigned)string[i] < 0x80)
		{
			lcd_showEN(string[i], starX + i*8, starY, bg_color, font_color);
			i++;
		}
		else
		{
			lcd_showCN(string+i, starX + i*8, starY, bg_color, font_color);
			i += 2;
		}
	}
}


void LCD_SetPic(unsigned starX, unsigned starY, unsigned w, unsigned h, char *pic)
{
	int i, j;
	unsigned pos = 0;
	RGB_COLOR color;
	
	for(i = 0; i < h; i++)
	{
		for(j = 0; j < w; j++)
		{
			color = pic[pos] | pic[pos + 1] << 8; //把char数据变为16图像数据
			LCD_SetPixel(starX + j, starY + i, color);
			pos +=2;
		}
	}
}



void LCD_SetPixel(unsigned x, unsigned y, rgb_t color)
{
	if(x >= LCD_WIDTH || y >= LCD_HIGH)
	{
		return;
	}
	frameBuffer[y][x] = color;
}

