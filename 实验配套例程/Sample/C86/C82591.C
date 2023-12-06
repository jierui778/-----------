/**********************************************************
 * 文件名: C82591.c
 * 文件描述: 每给主片8259一次脉冲，便产生一次中断，输出
 *     显示字符"7"。
 **********************************************************
 *                                西安唐都科教仪器公司
 **********************************************************/
 
#include "conio.h"

void interrupt mir7(void);

void main(void)
{
	_asm{ 
			push ds
			xor ax,ax
			mov ds,ax
			mov ax,offset mir7
			mov si,003ch
			mov [si],ax
			mov ax,cs
			mov si,003eh
			mov [si],ax
			cli
			pop ds       
		}
	// 主片8259初始化
	outportb(0x20, 0x11);		//ICW1
	outportb(0x21, 0x08);		//ICW2
	outportb(0x21, 0x04);		//ICW3
	outportb(0x21, 0x01);		//ICW4
	outportb(0x21, 0x6f);		//OCW1
	_asm sti
	while(1);
}

// 中断处理程序
void interrupt mir7(void)
{
	_AX = 0x0137;
	_asm int 10h
	_AX = 0x0120;
	_asm int 10h
	outportb(0x20, 0x20);		//清中断
}