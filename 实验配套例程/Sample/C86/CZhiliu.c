/***********************************************************
 * 文件名: Zhiliu.c
 * 功能描述: 直流电机闭环调速实验
 ***********************************************************/
 
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define M8255_A		0x600
#define M8255_B		0x602
#define M8255_C		0x604
#define M8255_CON	0x606

#define M8254_0		0x6c0
#define M8254_1		0x6c2
#define M8254_2		0x6c4
#define M8254_CON	0x6c6

void  interrupt irq6h (void);
void  interrupt irq7h (void);

void init(void);
void pid(void);
void put_com(void);
void m_main(void);
void delay(int time);

int mmul(int x,int y);				//16位乘法，溢出赋极值
int change32_16(int z,int t);		//将32位数转化成16位
char change16_8(int wd);			//将16位数转化成8位
int madd(int x,int y);				//16位加法，溢出赋极值

int TK=0x14,X=0x80;
int SPEC=0x30,IBAND=0x60,KP=8,TI=18,TD=32;
int CH1,CH2,CH3,UK,ZV,ZVV,TC,FPWM,UK_1,AAA1,VAA,BBB,VBB,MARK;
int YK,VADD,EK_1,AEK,BEK,EK;

int yyyy=0;

void main()
{
   init();
   _asm STI
   for(;;) m_main();
}

void delay(int time)
{
	int i;
	for(i=0;i<=time;i++);
	return;
}

void init(void)
{
	int m_ip;
  
	if(_CS==0) m_ip=0x2000;
	else m_ip=0x0000;

	_asm{
		push ds
		xor ax,ax
		mov ds,ax

		mov ax,offset irq6h
        add ax,m_ip
		mov si,0038h
		mov [si],ax
		mov ax,cs
		mov si,003ah
		mov [si],ax

		mov ax,offset irq7h
        add ax,m_ip
		mov si,003ch
		mov [si],ax
		mov ax,cs
		mov si,003eh
		mov [si],ax
		cli
		mov al,2fh
		out 21h,al
		pop ds
		}

	VADD=YK=EK=EK_1=AEK=BEK=ZV=ZVV=UK=UK_1=BBB=VBB=MARK=0x00;
	FPWM=0x01;TC=0x10;
	AAA1=VAA=0x7f;

	outp(M8255_CON,0x90);		//8255初始化
	outp(M8255_B,0x00);
	outp(M8254_CON,0x36);		//8254初始化
	outp(M8254_0,0xe8);			//计数值
	outp(M8254_0,0x03);

	return;
}

void m_main(void)
{
	for(;;) if(TK <= TC) break;

	TC=0x00;
	YK=ZVV;
	pid();
	if(UK <= 0x80)  AAA1=0x10;
	else AAA1=UK-0x80;
	BBB=0x7f-AAA1;
	CH1=SPEC;
	CH2=YK;
	CH3=UK;
	put_com();
	return;
}

void put_com(void)
{
	char temp;
	temp = inp(0x03fb);
	temp = temp&0x7f;
	outp(0x03fb, temp);
	for(;;)  if((inp(0x03fd)&0x40)!=0)	break;
	outp(0x03f8,CH1);

	for(;;)  if((inp(0x03fd)&0x40)!=0)	break;
	outp(0x3f8,CH2);
	
	for(;;)  if((inp(0x03fd)&0x40)!=0)	break;
	outp(0x3f8,CH3);

	return;
}

void pid(void)
{  
	int K,P,I,D;
	char z,t;

	K=P=I=D=0;
	EK=SPEC-YK;
	BEK=EK-EK_1-AEK;		//△2EK
	AEK=EK-EK_1;			//△EK

	if(abs(EK)>abs(IBAND)) I=0;
	else I=(EK*TK)/TI;

	P=AEK;
	D=((TD/TK)*BEK)/10000;

//△UK=KP*△EK + KI*Ek + KD*(△EK-△EK-1)  UK=△UK+UK-1
	K=madd(I,P);
	K=madd(D,K);
	K=mmul(K,KP);
	K=K/10;
	UK=K+UK_1;

/*将UK值转化成8位数据,取K的低8位值并取符号*/
	UK=change16_8(UK);
	UK_1=UK;
	EK_1=EK;
	UK=UK+X;
}

void interrupt irq6h(void)
{
	TC++;
	if (FPWM==0x01)
	{
		if(VAA!=0x00)
		{
			VAA=VAA-1;
			outp(M8255_B,0x01);
		}
		else
		{
			FPWM=0x02;
			VBB=BBB/2;
		}
	}

	if(FPWM==0x02)
	{
		if(VBB!=0x00)
		{
			VBB=VBB-1;
			outp(M8255_B,0x00);
		}
		else
		{
			FPWM=0X01;
			VAA=AAA1/2;
		}
	}
	_asm CLC

	if( MARK==0x01)
	{
		VADD=VADD+0x01;
		if( VADD > 0x0700 )
		{
			VADD=0x0700;
			MARK=0x00;
	    }
	}
	outp(0x20,0x20);
	return;
}

void interrupt irq7h(void)
{
	if(MARK==0x00)
		MARK=0x01;
	else
	{
		MARK=0x00;
		if(VADD!=0x00)
		{
			ZV=0x03E8/VADD;
			VADD=0x00;
		}
		ZVV=ZV;
	}
	outp(0x20,0x20);
	return;
}

int mmul( int x,int y)
{ 
	int s,t,z;
	s=x*y;
	z=_AX;
	t=_DX;
	s=change32_16(z,t);
	return(s);
}

int change32_16(int z,int t)   /*t=高字，z=低字*/
{ 
	int s;

	if(t==0)
	{
		if((z&0x8000)==0) s=z;
		else s=0x7fff;
	}
	else if ((t&0xffff)==0xffff)
	{
		if((z&0x8000)==0) s=0x8000;
		else s=z;
	}
	else if ((t&0x8000)==0) s=0x7fff;
	else s=0x8000;
	return(s);
}

int madd(int x,int y)
{
	int t;
	t=x+y;
	if(x>=0 && y>=0)			//同号相乘,符号位变反说明溢出
	{
		if((t&0x8000)!=0) t=0x7fff;}
		else if (x<=0 && y<=0)
		{ if((t&0x8000)==0) t=0x8000; }
	return(t);
}

char change16_8(int wd)			//t=高字节，z=低字节
{
	char z,t,s;

	_AX=wd;
	z=_AL;
	_AX=wd;
	t=_AH;

	if(t==0x00)
	{
		if((z&0x80)==0) s=z;
		else s=0x7f;
	}
	else if ((t&0xff)==0xff)
	{
		if((z&0x80)==0) s=0x80;
		else s=z;
	}
	else if((t&0x80)==0) s=0x7f;
	else s=0x80;

	return(s);

}