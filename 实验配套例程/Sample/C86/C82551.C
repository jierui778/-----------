/********************************************************
 * 文件名: C82551.c
 * 文件描述: 8255的A口输入，B口输出，将输入的数据从B口
 *     输出，观察灯的显示是否与输入一致。
 ********************************************************/
 
#include "conio.h"

#define M8255_A			0x600		//端口定义
#define M8255_B			0x602
#define M8255_C			0x604
#define M8255_CON		0x606

#define Read8255(x)			inportb(x)
#define Write8255(port,x)	outportb(port, x)

void main(void)
{
	unsigned char temp;
	Write8255(M8255_CON, 0x90);			//8255初始化
	while(1)
	{
		temp = Read8255(M8255_A);		//输入
		Write8255(M8255_B, temp);		//输出
	}
}