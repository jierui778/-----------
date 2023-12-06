/***************************************************
 * 文件名: CKeyScan.c
 * 功能描述: 使用8255完成键盘及数码管显示实验
 *************************************************** 
 *     8255的B口为数码管的段驱动，A口为列扫描及数码
 *     管位驱动，C口为行扫描。
 *     按下按键，该键对应值按顺序显示在数码管上。
 ***************************************************/

#include <stdlib.h>
#include <conio.h>

void dis(void);
void clear(void);
void ccscan(void);
void putbuf(void);
void getkey(void);
void delay(int time);

int MY8255_A    = 0x0600;
int MY8255_B    = 0x0602;
int MY8255_C    = 0x0604;
int MY8255_MODE = 0x0606;
// 数码管显示对应值代码
char a[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 
			0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71};

char b[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
int  cc;
int  b_n;
int  n;

void main()
{
   outp(MY8255_MODE, 0x81);		//写8255控制字
   b_n = 5;

   while(1)
   {
      dis();			//显示子程序
      clear();			//清屏子程序
      ccscan();			//键盘扫描子程序
      if (cc)
      {
		dis();
		delay(0x5);
		clear();
		ccscan();
		if (cc)
	 	{
	    	getkey();
	 	}
      }
   }
}
// 确定按下按键具体值
void getkey(void)
{
   int i;
   int j = 0xfe;

   for(i=0;i<=3;i++)
   {
      outp(MY8255_A, j);

      if ( !( (inp(MY8255_C)) & 0x01) )
      {
	 	n = i + 0;
	 	putbuf();
	 	return;
      }

      if ( !( (inp(MY8255_C)) & 0x02) )
      {
	 	n = i + 4;
	 	putbuf();
	 	return;
      }

      if ( !( (inp(MY8255_C)) & 0x04) )
      {
	 	n = i + 8;
	 	putbuf();
	 	return;
      }

      if ( !( (inp(MY8255_C)) & 0x08) )
      {
	 	n = i + 12;
	 	putbuf();
	 	return;
      }

      j <<= 1;
   }
}
// 按键扫描
void ccscan(void)
{
   outp(MY8255_A, 0x00);
   cc = inp(MY8255_C);
   cc = (~cc) & 0x0F;
}
// 显示
void dis(void)
{
   int i;
   int j = 0xdf;

   for(i=0;i<=5;i++)
   {
      outp(MY8255_A, 0xff);
      outp(MY8255_B, a[b[i]]);
      outp(MY8255_A, j);

      delay(0x5);
      j = (j>>1)|(j<<7);
   }
}
// 清屏
void clear(void)
{
   outp(MY8255_B, 0x00);
}

void putbuf(void)
{
   b[b_n] = n;
   b_n--;
   if (b_n == -1)
   {
      b_n = 5;
   }

   dis();
   clear();
   ccscan();
   while (cc)
   {
      dis();
      clear();
      ccscan();
   }
}

void delay(int time)
{
   int i;
   int j;
   for(i=0;i<=time;i++)
   {
      for(j=0;j<=0x100;j++)
      {   }
   }
   return;
}