/////////////////////////////////////////////////////////
// 文件名称: CLED16.C
// 功能描述:
//   行: CS1(600H), CS2(640H)  列: CS3(680H), CS4(6C0H)
/////////////////////////////////////////////////////////

#include "conio.h"
#include "Chzdot.h"					// 汉字字库

#define Row1(x) outportb(0x600, x)	// 定义端口
#define Row2(x) outportb(0x640, x)
#define Col1(x) outportb(0x680, x)
#define Col2(x) outportb(0x6c0, x)

void Delay(void)					// 延时子程序
{
	unsigned int x;
	for(x=0; x<50; x++);
}

void clear(void)					// 清除子程序
{
	Row1(0x00);
	Row2(0x00);
	Col1(0xff);
	Col2(0xff);
}

void main(void)
{
	unsigned char Scan=0x01, i, j;
	unsigned int count=0;
	clear();
	while(1)
	{
		for(i=0; i<200; i++)
		{
			for(j=0; j<8; j++)
			{
				Row1(0x00);
				Col1(~hzdot[count]);		// 列0--7
				Col2(~hzdot[count+1]);		// 列8--15
				count+=2;
				Row1(Scan);					// 行0--7
				Scan = (Scan<<1)|(Scan>>7);	// 行扫描
				Delay();
			}
			Row1(0x00);
			for(j=0; j<8; j++)
			{
				Row2(0x00);
				Col1(~hzdot[count]);
				Col2(~hzdot[count+1]);
				count+=2;
				Row2(Scan);					// 行8--15
				Scan = (Scan<<1)|(Scan>>7);	// 行扫描
				Delay();
			}
			Row2(0x00);
			count-=32;
		}
		count+=2;
		if(count==(352-32)) count=0;
	}
}