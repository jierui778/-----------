/*******************************************************
 * 文件名: LCD.C
 * 功能描述: 液晶控制实验
 *     显示"唐都科教仪器公司欢迎您！", 滚屏一周
 *******************************************************/

#include <conio.h>
#include "lcd.h"

void delay(int time);

void query(char cmd);
void openlight(char cmd);
void closelight(char cmd);
void clear(char cmd,int x);
void write(char cmd,char data);
void writehz(char xadd,char yadd,char cmd,char* hz);

int MY8255_A    = 0x0600;
int MY8255_B    = 0x0602;
int MY8255_C    = 0x0604;
int MY8255_MODE = 0x0606;

char cmd1 = 0x04;
char cmd2 = 0x08;
char data;
char xadd;
char yadd;

///////////////////////////////////////////////////////////////
void main()
{
	int x;
	outp(MY8255_MODE, 0x80);

	write(cmd1,0x3f);                    //Display On 打开显示
	write(cmd2,0x3f);

	write(cmd1,0xc0);                    //设置起始行
	write(cmd2,0xc0);

	for(x=0;x<8;x++)                     //清屏
	{
		clear(cmd1,x);
		clear(cmd2,x);
	}
										//写汉字
	writehz(0xba,0x40,cmd1,tang);
	writehz(0xba,0x50,cmd1,du);
	writehz(0xba,0x60,cmd1,ke);
	writehz(0xba,0x70,cmd1,jiao);
	writehz(0xba,0x40,cmd2,yi);
	writehz(0xba,0x50,cmd2,qi);
	writehz(0xba,0x60,cmd2,gong);
	writehz(0xba,0x70,cmd2,si);
	writehz(0xbc,0x60,cmd1,huan);
	writehz(0xbc,0x70,cmd1,ying);
	writehz(0xbc,0x40,cmd2,nin);
	writehz(0xbc,0x50,cmd2,gantan);

	delay(50);

	for(x=0xc1;x<=0xFF;x++)
	{
		write(cmd1,x);
		write(cmd2,x);
		delay(20);
	}
	while(1);
}
//////////////////////////////////////////////////////////////

void write(char cmd,char data)          //写命令或数据子程序
{
	outp(MY8255_B, data);
	cmd = cmd | 0x10;
	outp(MY8255_A, cmd);
	cmd = cmd & 0xEF;
	outp(MY8255_A, cmd);
}

void writehz(char xadd,char yadd,char cmd,char* hz)
{                                       //写汉字子程序 16*16
	int x,y;

	write(cmd,xadd);
	query(cmd+1);

	write(cmd,yadd);
	query(cmd+1);

	for(x=0;x<2;x++)
	{
		for(y=0;y<16;y++)
		{
			data = hz[y+(x*16)];
			write(cmd+2,data);
			query(cmd+1);
		}

		xadd++;
		write(cmd,xadd);
		query(cmd+1);

		write(cmd,yadd);
		query(cmd+1);
	}
}

void openlight(char cmd)                  //打开背景灯
{
	cmd = cmd | 0x20;
	outp(MY8255_A, cmd);
}

void closelight(char cmd)                 //关闭背景灯
{
	cmd = cmd & 0xdf;
	outp(MY8255_A, cmd);
}

void clear(char cmd,int x)                //清一页屏幕子程序
{
	int y;

	xadd = 0xb8+x;
	write(cmd,xadd);
	query(cmd+1);

	yadd = 0x40;
	write(cmd,yadd);
	query(cmd+1);

	for(y=0;y<64;y++)
	{
		data = 0x00;
		write(cmd+2,data);
		query(cmd+1);
	}
}

void query(char cmd)                      //查询子程序
{
	outp(MY8255_MODE, 0x82);

	cmd = cmd | 0x10;
	outp(MY8255_A, cmd);
	cmd = cmd & 0xEF;
	outp(MY8255_A, cmd);

	while( inp(MY8255_B) & 0x80)
	{
		cmd = cmd | 0x10;
		outp(MY8255_A, cmd);
		cmd = cmd & 0xEF;
		outp(MY8255_A, cmd);
	}

	outp(MY8255_MODE, 0x80);
}

void delay(int time)
{
	int i;
	int j;
	for(i=0;i<=time;i++)
	{
		for(j=0;j<=0x1000;j++);
	}
}
