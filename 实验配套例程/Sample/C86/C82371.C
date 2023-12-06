/*********************************************************
 * 文件名: C82371.c
 * 功能描述: 将SRAM单元1000H单元的数据通过DMA的方式转移
 *     到0000H单元
 *********************************************************/
 
#include "conio.h"

#define ch0_add		0x600
#define ch1_add		0x604
#define ch2_add		0x608
#define ch3_add		0x60c
#define ch0_count	0x602
#define ch1_count	0x606
#define ch2_count	0x60a
#define ch3_count	0x60e

#define mode		0x616
#define req			0x612
#define mask		0x614
#define mling		0x610
#define tempm		0x61a
#define mainmask	0x61e

#define Rdata(port)		inportb(port)
#define Wdata(port, x)	outportb(port, x)

typedef unsigned char uchar ;
typedef unsigned int  uint  ;

void main(void)
{
	uchar i;
	uchar *src;
	src = (uchar *)0x80002000;
	for(i=0; i<16; i++)
	{
		*src = i;
		src++;
		src++;
	}
	Wdata(tempm, 0x00);			//发总清命令（复位）
	Wdata(ch0_add, 0x00);		//通道0首址
	Wdata(ch0_add, 0x10);		//
	Wdata(ch1_add, 0x00);		//通道1首址
	Wdata(ch1_add, 0x00);		//
	Wdata(ch0_count, 0x0f);		//传输字节数
	Wdata(ch0_count, 0x00);		//
	Wdata(ch1_count, 0x0f);		//传输字节数
	Wdata(ch1_count, 0x00);		//
	Wdata(mode, 0x88);			//通道0方式字
	Wdata(mode, 0x85);			//通道1方式字
	Wdata(mling, 0x81);			//命令字
	Wdata(req, 0x04);			//请求字
	Wdata(mainmask, 0x00);		//总屏蔽
	while(1);
}