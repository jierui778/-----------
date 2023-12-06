/******************************************************
 * 文件名: DAC2.C
 * 文件说明: 使DA输出方波
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
	while(1)
	{	   
		wdata(0x600, 0x00);
		delay(0x5000);
		wdata(0x600, 0x7f);
		delay(0x5000);
	}
}
