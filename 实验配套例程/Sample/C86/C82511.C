/*********************************************************
 * 文件名: C82511.C
 * 功能描述: 研究8251串行传输的数据格式
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
	outportb(M8254_2, 0x1B);
	outportb(M8254_2, 0x3A);
	
	Reset_8251();
	delay();
	outportb(M8251_CON, 0x7e);		// 写8251方式字
	delay();
	outportb(M8251_CON, 0x34);		// 写8251控制字
}

//======发送子程序======
void Send(void)
{
	outportb(M8251_CON, 0x31);
	outportb(M8251_DATA, 0x55);
}

void main(void)
{
	init_sys();
	while(1)
	{
		Send();
		delay();
	}
}