/********************************************
 * 文件名: CMEM.C
 * 说明:   存储器实验，将0000H～000FH存入存
 *         储器单元，起始地址为80000
 ********************************************/
 	
void main(void)
{
	unsigned int *Addr;
	unsigned int i;
	Addr = (unsigned int *)0x80000000;
	for(i=0; i<16; i++)
	{
		*Addr = i;
		Addr += 1;
	}
	while(1);
}