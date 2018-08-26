#include <s3c2440.h>
#include <string.h>
#include "lcd.h"
#include "type.h"

//1.LCDCON1�Ŀ��ƼĴ�������
#define CLKVAL	(4 << 8)	//���ù�ʽ:VCLK=HCLK / [(CLKVAL + 1) �� 2]	(CLKVAL��0)
#define MMODE		(0 << 7)	//VM����Ƶ�ʣ�TFT���ã�����Ϊ0
#define	PNRMODE	(3 << 5)	//��ʾģʽ TFT 11
#define	BEEMODE (12 << 1)	//���ص�λ����TFT  16λģʽ��1100
#define	ENVID 	(0 << 0)	//������Ƶ�����Ҳ����ENλ����Ĭ�Ϲر�
#define LCDCON_VAL1	(CLKVAL | MMODE | PNRMODE | BEEMODE | ENVID)

//2.LCDCON2
#define	VBPD		(2 << 24)	//��ֱͬ���ź����ں���Ч������
#define	LINEVAL	((LCD_HIGH-1) << 14)	//LCD�Ĵ�ֱ�ߴ磨�߶ȣ�
#define	VFPD		(2 << 6)		//��ֱͬ�������ź�
#define	VSPW		(10 << 0)
#define LCDCON_VAL2	(VBPD | LINEVAL | VFPD | VSPW)

//LCDCON3
#define		HBPD		(2 << 19)
#define		HOZVAL	((LCD_WIDTH-1) << 8)
#define		HFPD		(2 << 0)
#define		LCDCON_VAL3	(HBPD | HOZVAL | HFPD)

//LCDCON4
#define		HSPW		(40 << 0)		//TYP=41��׼�ټ�1
#define		LCDCON_VAL4	HSPW

//LCDCON5
#define		BPP24BL		(0 << 12)
#define		FRM565		(1 << 11)
//ʱ��ͼ���ŷ�ת����
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

//LCD������������������
#define LCDBASE	((unsigned long)G_lcdBuffer)

//���û�������ַ
#define		LCDBANK		(((LCDBASE >>22) & 0x1FF) << 21)
#define		LCDBASEU	((LCDBASE >>1) & 0x1FFFFF << 0)
#define		vLCDADDR1	(LCDBANK | LCDBASEU)

#define		LCDBASEL		(((LCDBASE + LCD_WIDTH * LCD_HIGH * 2) >> 1) & 0x1FFFFF)
#define		vLCDADDR2		LCDBASEL

#define		OFFSIZE		0x0
#define		PAGEWIDTH (LCD_WIDTH)
#define		vLCDADDR3		(OFFSIZE | PAGEWIDTH)

//֡������ һ֡�����ݣ����е����ص㣬16λ
typedef unsigned short RGB_COLOR;
volatile RGB_COLOR frameBuffer[LCD_HIGH][LCD_WIDTH];//���ǿ�480


void ptr(char picture[])
{
	memcpy((char *)G_lcdBuffer,picture,480*272*2);
}



/****************************************
* ��������void lcd_init(void);
* �������ܣ�
* ����������
* ��������ֵ;
* �޸�ʱ�䣺
*****************************************/
void lcd_init()
{
	//1.��������
	GPCCON = 0xAAAAFEAB;
	GPDCON = 0xAAAAAAAA;
	GPGCON |= (0x3 << 8); 
	
	//2.���üĴ��������ƼĴ���
	LCDCON1 =LCDCON_VAL1;
	LCDCON2 =LCDCON_VAL2;
	LCDCON3 =LCDCON_VAL3;
	LCDCON4 =LCDCON_VAL4;
	LCDCON5 =LCDCON_VAL5;
	
	//3.���û�������ַ
	LCDSADDR1 = vLCDADDR1;
	LCDSADDR2 = vLCDADDR2;
	LCDSADDR3 = vLCDADDR3;
	
	//4.��LCD�ĵ�Դ
	BIT_SET(LCDCON5,3);
	BIT_SET(LCDCON1,0);
	
	memset((void*)G_lcdBuffer,110,sizeof(G_lcdBuffer));
	lcd_clean(0,0,LCD_WIDTH,LCD_HIGH,BLUE);
}

 /****************************************
* ��������void lcd_deinit(void);
* �������ܣ�
* ����������
* ��������ֵ;
* �޸�ʱ�䣺
*****************************************/
void lcd_deinit()
{}

/*********************************
 *�������ƣ�void LCD_setpixel(int x, int y, rgb_t color)
 *�������ܣ����
 *����������
 *��������ֵ����
*********************************/
void lcd_setpixel(int x, int y, rgb_t color)
{
	if(x < 0 || x >=LCD_WIDTH || y < 0 || y >= LCD_HIGH)
		return ;
	
	G_lcdBuffer[y][x] = color;
}
	
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
��������void lcd_showpic(int x,int y,int w,int h,char *pic)
�������ܣ���ʾһ�������ڴ������ͼ
����������
@int x ����ʼ������
@int y ����ʼ������
@int w ����	
@int h ����
@char *pic��ͼƬ��ַ
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
��������void lcd_showEn(int x,int y,char en,rgb_t fgcolor,rgb_t bgcolor)
�������ܣ�����������ʾһ�������ڴ������ַ�
����������
@int x ����ʼ������
@int y ����ʼ������
@char en��Ҫ��ӡ��Ӣ���ַ�
@rgb_t fgcolor��ǰ��ɫ���ַ�����ɫ
@rgb_t bgcolor������ɫ���ַ��������ɫ
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
��������void lcd_showCn(int x,int y,char cn[2],rgb_t fgcolor,rgb_t bgcolor)
�������ܣ�����������ʾһ�������ڴ������ַ�
����������
@int x ����ʼ������
@int y ����ʼ������
@char en[2]��Ҫ��ӡ���������ַ�
@rgb_t fgcolor��ǰ��ɫ���ַ�����ɫ
@rgb_t bgcolor������ɫ���ַ��������ɫ
*******************************************************************/
void lcd_showCn(int x,int y,char cn[2],rgb_t fgcolor,rgb_t bgcolor)
{
	int row = cn[0] - 0xA1;
	int col = cn[1] - 0xA1;
	cn_word_t pWord = CNBASE[row*94+col];//��ǰ���ֵĵ�������
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
��������void lcd_showCn(int x,int y,char cn[2],rgb_t fgcolor,rgb_t bgcolor)
�������ܣ�����������ʾһ�������ڴ������ַ�
����������
@int x ����ʼ������
@int y ����ʼ������
@char en[128]��Ҫ��ӡ����Ӣ���ַ���
@rgb_t fgcolor��ǰ��ɫ���ַ�����ɫ
@rgb_t bgcolor������ɫ���ַ��������ɫ
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
	cn_word_t pWord = CNBASE[row*94+col];//��ǰ���ֵĵ�������
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
 * ��������LCD_SetBackGround
 * ���ã���ӡ������ɫ
 * ������
 * 		@color: ��ӡ����ɫ
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
 * ��������Print_Bmp
 * ���ã����ٴ�ӡ����ͼƬ
 * ������
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
	cn_word_t pWord = CNBASE[row*94+col];//��ǰ���ֵĵ�������
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
 * ��������lcd_showEN
 * ���ã���ӡһ��Ӣ���ַ�
 * ������
 * 		@en����Ҫ��ӡ���ַ�
 * 		@starX: Ӣ���ַ�����ʼ�������
 *		@starY: Ӣ���ַ�����ʼ��������
 * 		@font_color��ǰ��ɫ
 * 		@bg_color: ����ɫ
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
			color = pic[pos] | pic[pos + 1] << 8; //��char���ݱ�Ϊ16ͼ������
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

