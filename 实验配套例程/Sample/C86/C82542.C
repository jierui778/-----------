/*********************************************************
 * 文件名: C82542.c
 * 功能描述: 应用8254的定时功能，产生1ms的方波波形，通过
 *     示波器观察
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

void main(void)
{
	//初始化8254
	Wdata(M8254_CON, 0x36);
	Wdata(M8254_A, 0xe8);
	Wdata(M8254_A, 0x03);
	
	Wdata(M8254_CON, 0x76);
	Wdata(M8254_B, 0xe8);
	Wdata(M8254_B, 0x03);
	
	while(1);
}
