/*********************************************************
 * 文件名: C82513.C
 * 功能描述: 8251双机通讯实验。接收机端程序。将接收到的
 *           数据存放在起始地址为0000:3000的空间并显示。
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
	unsigned char count, temp;
	unsigned char *Rcv_Addr;
	Rcv_Addr = (unsigned char *)0x00003000;
	init_sys();
	_AX = 0x0152;
	_asm INT 10h		// 输出显示'R'
	for(count=0; count<10; count++)
	{
		while(1)
		{	//判断是否接收到数据
			temp=inportb(M8251_CON);
			if((temp&0x02)==0x02) break;
		}
		*Rcv_Addr = inportb(M8251_DATA);
		Rcv_Addr++;
	}
	*Rcv_Addr = 0x00;
	_asm{					//ASCII码显示，发送方应发送ASCII
			mov ax, 0000h	//码，否则会显示乱码
			mov ds, ax
			mov AH, 06h
			mov BX, 3000h;
			INT 10h
		}
	while(1);
}