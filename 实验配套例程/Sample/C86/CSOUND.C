/*******************************************************
 * 文件名: CSOUND.C
 * 功能描述: 使用8254进行乐曲演奏
 *******************************************************/
 
#include "conio.h"

#define M8254_A		0x600
#define M8254_B		0x602
#define M8254_C		0x604
#define M8254_CON	0x606
#define Wdata(port, x)	outportb(port, x)

typedef unsigned char uchar;
typedef unsigned int  uint;

long Clk=0x0f4240;   //输入频率为1MHz=F4240


//======频率表======
static uint freq_tab[]={371,495,495,495,624,556,495,556,624,
						495,495,624,742,833,833,833,742,624,
						624,495,556,495,556,624,495,416,416,371,
						495,833,742,624,624,495,556,495,556,833,
						742,624,624,742,833,990,742,624,624,495,
						556,495,556,624,495,416,416,371,495,0};
//======时间表======
static uchar time_tab[]={4,  6,  2,  4,  4,  6,  2,  4,  4,
						 6,  2,  4,  4, 12,  1,  3,  6,  2,
						 4,  4,  6,  2,  4,  4,  6,  2,  4,  4,
						12,  4,  6,  2,  4,  4,  6,  2,  4,  4,
						 6,  2,  4,  4, 12,  4,  6,  2,  4,  4,
						 6,  2,  4,  4,  6,  2,  4,  4,  12};
//======基本延时程序======
void delay(uint x)
{
	uint i, j;
	for(i=0; i<x; i++)
	{
		for(j=0; j<0x5000; j++);
	}
}
uint Val_cnt;
int aaaa;
void main(void)
{
	uchar count=0;
	uchar tmpL, tmpH;
	while(1)
	{
		Val_cnt = Clk/freq_tab[count];
		tmpL = (uchar)(Val_cnt&0xff);
		tmpH = (uchar)((Val_cnt>>8)&0xff);
	    Wdata(M8254_CON, 0x36);    //定时器0、方式3
	    Wdata(M8254_A, tmpL);
        Wdata(M8254_A, tmpH);      //写计数值
        time_tab[count]=time_tab[count]*3;
        delay(time_tab[count]);
		count++;
		if(freq_tab[count]==0x00) count=0x00;  //判断乐曲结束
	}
}

