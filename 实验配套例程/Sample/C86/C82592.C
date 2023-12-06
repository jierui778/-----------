/**********************************************************
 * 文件名: C82592.c
 * 文件描述: 中断优先级实验，每给主片8259的IR6一次脉冲，便
 *     产生一次中断，输出显示字符"M6",若给主片8259的IR7一
 *     次脉冲，输出显示字符"M7"。先后按动KK1+、KK2+按键，
 *	   观察中断优先级响应是否正确。
 **********************************************************
 *                                西安唐都科教仪器公司
 **********************************************************/
 
#include "conio.h"

void interrupt mir6(void);
void interrupt mir7(void);

void delay(unsigned int i)
{
	unsigned int j;
	for(j=0; j<i; j++);
}


void main(void)
{
	_asm{ 
			push ds
			xor ax,ax
			mov ds,ax
			mov ax,OFFSET mir6
			mov si,0038h
			mov [si],ax
			mov ax,cs
			mov si,003ah
			mov [si],ax
			
			mov ax,OFFSET mir7
			mov si,003ch
			mov [si],ax
			mov ax,cs
			mov si,003eh
			mov [si],ax
			cli
			pop ds       
		}
	//主片8259初始化
	outportb(0x20, 0x11);		//ICW1
	outportb(0x21, 0x08);		//ICW2
	outportb(0x21, 0x04);		//ICW3
	outportb(0x21, 0x01);		//ICW4
	outportb(0x21, 0x2F);		//OCW1

	_asm sti
	while(1);
}

// 主片8259中断处理程序
void interrupt mir6(void)
{	_asm sti
	delay(0xc000);
	_AX = 0x014d;
	_asm int 10h
	_AX = 0x0136;
	_asm int 10h
	_AX = 0x0120;
	_asm int 10h
	outportb(0x20, 0x20);		//清中断
}

// 主片8259中断处理程序
void interrupt mir7(void)
{	_asm sti
	delay(0xc000);
	_AX = 0x014d;
	_asm int 10h
	_AX = 0x0137;
	_asm int 10h
	_AX = 0x0120;
	_asm int 10h
	outportb(0x20, 0x20);		//清中断
}


