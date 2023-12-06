/******************************************************
 * 文件名: DAC1.C
 * 文件说明: 使DA输出锯齿波
 ******************************************************/
 
#include "conio.h"

typedef unsigned char  uchar;
typedef unsigned int   uint;
#define wdata(Addr, Val)  (outp(Addr, Val))

void delay(uint count)
{
	uint i;
	for(i=0; i<count; i++);
} 

void main(void)
{
	uchar i=0;	
	while(1)
	{
		wdata(0x600, i);
		delay(0x300);
		i++;
	}
}
