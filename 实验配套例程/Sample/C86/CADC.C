/********************************************
 * 文件名: ADC1.C
 * 功能描述: AD采样，将采样值进行显示
 ********************************************/

#include "conio.h"

typedef   unsigned int  uint;
typedef   unsigned char uchar;

#define  Start (outportb(0x600, 0x00))		// 启动AD
#define  Read  (inportb(0x600))				// 读AD采样结果

void delay(uint count)
{
	uint i;
	for(i=0; i<count; i++);
}

// 显示多个字符
void dispm(uchar *src, uchar len)
{
	uchar i;
	for(i=0; i<len; i++)
	{
		_AL=*src;
		_asm{
		mov AH, 01h
		int 10h
		}
		src++;
	}
}

// 显示单个字符
void disps(uchar val)
{
	_AL=val;
	_asm{
	mov ah, 01h
	int 10h
	}
}

// Hex转换为ASC码，转换低4位
uchar Hex2AscL(uchar val)
{
	//uchar temp;
	val &= 0x0f;
	if(val>9)
		val+=0x37;
	else
		val+=0x30;
	return val;
}
// Hex转换为ASC码，转换高4位
uchar Hex2AscH(uchar val)
{
	//uchar temp;
	val=(val&0xf0)>>4;
	if(val>9)
		val+=0x37;
	else
		val+=0x30;
	return val;
}

static uchar flag[]="DAC0809 IN0: ";
static uchar kg[]="        ";
void main()
{
	while(1)
	{
		uchar ADval;
		Start;				// 启动AD采样
		delay(0x100);
		ADval=Read;			// 读采样结果
		dispm(flag, 13);	// 显示: DAC0809 IN0: 
		disps(Hex2AscH(ADval));		// 显示高位
		disps(Hex2AscL(ADval));		// 显示低位
		dispm(kg, 8);
		delay(0xf000);
		delay(0xf000);
	}
}