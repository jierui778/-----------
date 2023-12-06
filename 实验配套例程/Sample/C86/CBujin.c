/*********************************************************
 * 文件名: Bujin.c
 * 文件描述: 控制四相八拍步进电机顺时针转动
 *********************************************************/
 
#include "conio.h"

// 端口定义
#define M8255_A		0x600
#define M8255_B		0x602
#define M8255_C		0x604
#define M8255_CON	0x606

typedef unsigned char uchar;
typedef unsigned int  uint ;

// 各步控制值
static uchar btab[]={0x01,0x03,0x02,0x06,0x04,0x0c,0x08,0x09};

void delay(uint count)
{
	uint i;
	for(i=0; i<count; i++);
}

void main(void)
{
	uchar i;
	outportb(M8255_CON, 0x90);
	while(1)
	{
		for(i=0; i<8; i++)
		{
			outportb(M8255_B, btab[i]);
			delay(0xf000);
		}
	}
}