/********************************************************
 * 文件名: C82551.c
 * 文件描述: 8255的A口,B口均为输出，使D0～D7从左向右循环
 *     亮一灯，使D8～D15从右向左循环亮一灯。
 ********************************************************/
 
#include "conio.h"

#define M8255_A			0x600		//端口定义
#define M8255_B			0x602
#define M8255_C			0x604
#define M8255_CON		0x606

#define Read8255(x)			inportb(x)
#define Write8255(port,x)	outportb(port, x)

void delay(unsigned int i)
{
	unsigned int j;
	for(j=0; j<i; j++);
}

void main(void)
{
	unsigned char temp1, temp2;
	Write8255(M8255_CON, 0x80);			//8255初始化
	temp1 = 0x80;
	temp2 = 0x01;
	while(1)
	{
		Write8255(M8255_A, temp1);
		temp1 = (temp1>>1)|(temp1<<7);
		Write8255(M8255_B, temp2);		//输出
		temp2 = (temp2<<1)|(temp2>>7);
		delay(0xc000);
		delay(0xc000);
	}
}