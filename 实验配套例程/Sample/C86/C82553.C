/*********************************************************
 * 文件名: C82553.c
 * 功能描述: 本实验使8255端口A工作在方式0并作为输出口，
 * 		 	 端口B工作在方式1并作为输入口
 *********************************************************
 *                                  西安唐都科教仪器公司
 *********************************************************/
 
#include "conio.h"

#define M8255_A		0x600
#define M8255_B		0x602
#define M8255_C		0x604
#define M8255_CON	0x606

#define Rdata(port)			inportb(port)
#define Wdata(port, x)		outportb(port, x)


void interrupt mir7(void);

void main(void)
{
	_asm{
		PUSH DS
		MOV AX, 0000H
		MOV DS, AX
		MOV AX, OFFSET mir7		//取中断入口地址
		MOV SI, 003CH			//中断矢量地址
		MOV [SI], AX			//填IRQ7的偏移矢量
		MOV AX, CS				//段地址
		MOV SI, 003EH
		MOV [SI], AX			//填IRQ7的段地址矢量
		CLI
		POP DS
		}
		
								//初始化主片8259
	Wdata(0x20, 0x11);			//ICW1
	Wdata(0x21, 0x08);			//ICW2
	Wdata(0x21, 0x04);			//ICW3
	Wdata(0x21, 0x01);			//ICW4
	Wdata(0x21, 0x6f);			//OCW1
								
	Wdata(M8255_CON, 0x86);		//初始化8255
	Wdata(M8255_CON, 0x05);


	_asm sti
	while(1);
}

//中断处理程序
void interrupt mir7(void)
{		unsigned char temp;
		temp = Rdata(M8255_B)	;		//输入
		Wdata(M8255_A, temp);		//输出
		outportb(0x20, 0x20);		//清中断
}