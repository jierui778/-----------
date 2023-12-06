/*********************************************************
 * 文件名: C82512.C
 * 功能描述: 8251双机通讯实验。发送机端程序。发送源地
 *           址为0000:3000
 *********************************************************/
 
#include "conio.h"
typedef unsigned char uchar;
#define M8254_2		0x0644		//端口定义
#define M8254_CON	0x0646

#define M8251_DATA	0x0600
#define M8251_CON	0x0602

void delay(void)
{
	unsigned int i;
	for(i=0; i<5000; i++);
}

//======复位8251======
void Reset_8251(void)
{
	unsigned char i;
	for(i=0; i<3; i++)
	{
		outportb(M8251_CON, 0x00);
		delay();
	}
	outportb(M8251_CON, 0x40);
}

//======初始化======
void init_sys(void)
{
	outportb(M8254_CON, 0xb6);		// 初始化8254
	outportb(M8254_2, 0x0c);
	outportb(M8254_2, 0x00);
	
	Reset_8251();
	delay();
	outportb(M8251_CON, 0x7e);		// 写8251方式字, 波特率9600
	delay();
	outportb(M8251_CON, 0x34);		// 写8251控制字
}

//======发送子程序======
void Send(uchar *src, uchar num)
{
	uchar i, j, temp;
	uchar *Sd_data;
	Sd_data = src;
	for(i=0; i<num; i++)
	{
		outportb(M8251_CON, 0x31);
		outportb(M8251_DATA, *Sd_data);
		while(1)
		{
			temp=inportb(M8251_CON);
			if((temp&0x01)==0x01) break ;
		}
		Sd_data++;
		for(j=0; j<10; j++) delay();
	}
}

void main(void)
{
	uchar *Send_Addr;
	init_sys();
	Send_Addr = (uchar *)0x00003000;
	Send(Send_Addr, 10);
	while(1);
}