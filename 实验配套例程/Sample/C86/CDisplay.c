/*********************************************************
 * 文件名: CDisplay.c
 * 文件描述: 屏幕打印程序，通过功能调用将A--Z在显示屏上
 *     显示。
 *********************************************************
 *                               西安唐都科教仪器公司
 *********************************************************/
 
void delay(unsigned int x)
{
	unsigned int i;
	for(i=0; i<x; i++);
}

void main(void)
{
	unsigned char count;
	for(count=0x41; count<0x5B; count++)
	{
		_DL = count;
		_asm{
			mov AH, 02H
			int 21H
			}
		delay(0xf000);
	}
	while(1);
}