/*********************************************************
 * 文件名: C82372.c
 * 功能描述: I/O到存储器DMA传输实验
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

#define M8255_CON	0x646

#define Rdata(port)			inportb(port)
#define Wdata(port, x)		outportb(port, x)

typedef unsigned char uchar ;
typedef unsigned int  uint  ;

void main(void)
{
	Wdata(M8255_CON, 0x82);		//初始化8255

	Wdata(tempm, 0x00);			//发总清命令（复位）

	Wdata(ch1_add, 0x21);		//;写通道1当前地址寄存器
	Wdata(ch1_add, 0x03);		

	Wdata(mode, 0x45);			//通道1方式字

	Wdata(mling, 0x80);			//命令字

	Wdata(req, 0x05);			//请求字

	Wdata(mainmask, 0x00);		//总屏蔽

	while(1);
}