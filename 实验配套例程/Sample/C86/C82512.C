/*********************************************************
 * 文件名: C82512.C
 * 功能描述: 8251自收自发实验。发送源地址为0000:4000，接
 *           收到的数据存放在起始地址为0000:3000的空间。
 *********************************************************/
 
#include "conio.h"

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

void main(void)
{
	unsigned char i;
	unsigned char count, temp1, temp2;
	unsigned char *Send_Addr, *Rcv_Addr;
	init_sys();
	Send_Addr = (unsigned char *)0x00004000;
	Rcv_Addr = (unsigned char *)0x00003000;
	for(count=0; count<10; count++)
	{
		temp1=*Send_Addr;
		outportb(M8251_CON, 0x37);
		outportb(M8251_DATA, temp1);
		while(1)
		{
			temp2=inportb(M8251_CON);
			if((temp2&0x01)==0x01) break;			//判断发送缓冲区是否空
		}
		for(i=0; i<10; i++)	delay();
		while(1)
		{
			temp2=inportb(M8251_CON);
			if((temp2&0x02)==0x02) break;			//判断是否接收到数据
		}
		*Rcv_Addr = inportb(M8251_DATA);
		Send_Addr++;
		Rcv_Addr++;
	}
	while(1);
}