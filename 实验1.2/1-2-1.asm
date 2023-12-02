;将ASCII码表示的十进制数转换为二进制数
PUBLIC SADD
SSTACK SEGMENT STACK
		   DW 64 DUP(?)
SSTACK ENDS
DATA SEGMENT
	SADD DB 30H,30H,32H,35H,36H;  ; 存储ASCII码表示的十进制数
DATA ENDS
CODE      SEGMENT
		  ASSUME CS:CODE,DS:DATA
START:    MOV    AX, DATA        ; 将DATA段的地址加载到AX寄存器
		  MOV    DS, AX          ; 将AX寄存器的值移动到DS寄存器
		  MOV    AX, OFFSET SADD  ; 将SADD的偏移地址加载到AX寄存器
		  MOV    SI, AX          ; 将AX寄存器的值移动到SI寄存器
		  MOV    BX, 000AH       ; 将十进制数10加载到BX寄存器
		  MOV    CX, 0004H       ; 将十进制数4加载到CX寄存器
		  MOV    AH, 00H         ; 将AH寄存器清零
		  MOV    AL, [SI]        ; 将SI指向的内存位置的值加载到AL寄存器
		  SUB    AL, 30H         ; 将AL寄存器的值减去30H
A1:       IMUL   BX               ; 乘法运算，将AL乘以BX
		  MOV    DX, [SI+01]      ; 将下一个字节的值存储到DX寄存器
		  AND    DX, 00FFH        ; 将DX寄存器的高字节清零
		  ADC    AX, DX           ; 将DX加到AX中
		  SBB    AX, 30H          ; 将30H减去AX的值
		  INC    SI               ; SI寄存器加1，指向下一个字节
		  LOOP   A1               ; 循环执行A1标签处的指令，直到CX为0
A2:       JMP    A2               ; 无限循环
CODE ENDS
END START
