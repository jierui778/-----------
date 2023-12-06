/**********************************************************
 * 文件名: C82593.c
 * 文件描述: 中断级联实验，每给主片8259的IR7一次脉冲，便
 *     产生一次中断，输出显示字符"M7",若给从片8259的IR1一
 *     次脉冲，输出显示字符"S1"。
 **********************************************************
 *                                西安唐都科教仪器公司
 **********************************************************/
 
#include "conio.h"

void interrupt mir7(void);
void interrupt sir1(void);

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
			
			mov ax, OFFSET sir1
			mov si, 00c4h
			mov [si], ax
			mov ax, cs
			mov si, 00c6h
			mov [si], ax
			cli
			pop ds       
		}
	//主片8259初始化
	outportb(0x20, 0x11);		//ICW1
	outportb(0x21, 0x08);		//ICW2
	outportb(0x21, 0x04);		//ICW3
	outportb(0x21, 0x01);		//ICW4
	outportb(0x21, 0x6b);		//OCW1
	//从片8259初始化
	outportb(0xa0, 0x11);		//ICW1
	outportb(0xa1, 0x30);		//ICW2
	outportb(0xa1, 0x02);		//ICW3
	outportb(0xa1, 0x01);		//ICW4
	outportb(0xa1, 0xfd);		//OCW1
	
	_asm sti
	while(1);
}

// 主片8259中断处理程序
void interrupt mir7(void)
{
	_AX = 0x014d;
	_asm int 10h
	_AX = 0x0137;
	_asm int 10h
	_AX = 0x0120;
	_asm int 10h
	outportb(0x20, 0x20);		//清中断
}

// 从片8259中断处理程序
void interrupt sir1(void)
{
	_AX = 0x0153;
	_asm int 10h
	_AX = 0x0131;
	_asm int 10h
	_AX = 0x0120;
	_asm int 10h
	outportb(0xa0, 0x20);
	outportb(0x20, 0x20);
}