/*********************************************************
 * �ļ���: CDisplay.c
 * �ļ�����: ��Ļ��ӡ����ͨ�����ܵ��ý�A--Z����ʾ����
 *     ��ʾ��
 *********************************************************
 *                               �����ƶ��ƽ�������˾
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