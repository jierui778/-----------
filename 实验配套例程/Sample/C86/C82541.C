/*********************************************************
 * 文件名: C82541.c
 * 功能描述: 应用8254的计数功能，每按键5次产生一次中断，
 *     输出显示字符'M'
 *********************************************************
 *                                  西安唐都科教仪器公司
 *********************************************************/
 
#include "conio.h"

#define M8254_A		0x600
#define M8254_B		0x602
#define M8254_C		0x604
#define M8254_CON	0x606

#define Rdata(port)		inportb(port)
#define Wdata(port, x)	outportb(port, x)

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
	//初始化8254
	Wdata(M8254_CON, 0x10);
	Wdata(M8254_A, 0x04);
	
	_asm sti
	while(1);
}

//中断处理程序
void interrupt mir7(void)
{
	Wdata(M8254_A, 0x04);
	_AH = 0x01;					//显示字符'M'
	_AL = 'M';
	_asm int 10h
	_AX = 0x0120;
	_asm int 10h
	Wdata(0x20, 0x20);
}