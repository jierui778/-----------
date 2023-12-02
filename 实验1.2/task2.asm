; 二进制转换BCD码

SSTACK SEGMENT STACK
	DW 64 DUP(?)
SSTACK ENDS

DATA SEGMENT
	SADD DB 00H,10H,10H,00H,01H,00H,01H,10H ; 存储二进制数的数组
DATA ENDS

CODE SEGMENT
	ASSUME CS:CODE,DS:DATA,SS:SSTACK

MAIN PROC FAR
START:
		MOV AX,DATA ; 将数据段的地址加载到AX寄存器
		MOV DS,AX ; 将AX寄存器的值存入DS寄存器
		MOV AX,SSTACK ; 将堆栈段的地址加载到AX寄存器
		MOV SS,AX ; 将AX寄存器的值存入SS寄存器

                MOV AX,OFFSET SADD ; 将SADD的偏移地址加载到AX寄存器
                MOV SI,AX ; 将AX寄存器的值存入SI寄存器
                MOV BX,0004H ; 将十六进制数0F存入BX寄存器
                MOV CX,0007H ; 将十六进制数04存入CX寄存器
                MOV AL,[SI] ; 将SI指向的内存单元的值加载到AL寄存器
                XOR DX,DX ; 清空DX寄存器

		AND AX,0003H ; 将AX寄存器与0003H进行按位与运算
T1:		IMUL BX ; 将BX寄存器与AX寄存器相乘，并将结果存入AX寄存器
		INC SI ; 将SI寄存器的值加1
		MOV DL,[SI] ; 将SI指向的内存单元的值加载到DL寄存器

                PUSH AX ; 将AX寄存器的值压入堆栈
                PUSH BX ; 将BX寄存器的值压入堆栈
                PUSH CX ; 将CX寄存器的值压入堆栈

                MOV CL,03H ; 将十六进制数03存入CL寄存器
                XOR BL,BL ; 清空BL寄存器
                MOV BL,DL ; 将DL寄存器的值存入BL寄存器
                AND DL,0FH ; 将DL寄存器与0FH进行按位与运算
                SHR BL,CL ; 将BL寄存器的值右移3位
                ADD DL,BL ; 将DL寄存器与BL寄存器相加

                POP CX ; 将堆栈中的值弹出到CX寄存器
                POP BX ; 将堆栈中的值弹出到BX寄存器
                POP AX ; 将堆栈中的值弹出到AX寄存器

		AND DX,00FFH ; 将DX寄存器与00FFH进行按位与运算
		ADC AX,DX ; 将DX寄存器的值与AX寄存器的值相加，并将结果存入AX寄存器
		DEC CX ; 将CX寄存器的值减1
		JNZ T1 ; 如果CX寄存器的值不为0，则跳转到标签T1处
T2:		JMP T2 ; 无条件跳转到标签T2处
		RET ; 返回

	MAIN ENDP
CODE ENDS
	END START