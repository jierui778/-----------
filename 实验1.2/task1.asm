; 将ASCII码表示的十进制转化为十六进制
PUBLIC SADD; 可以被外部调用
SSTACK SEGMENT STACK
    DW 64 DUP(?) ; 定义栈空间
SSTACK ENDS
DATA SEGMENT
SADD DB 30H,32H,35H,36H ; 存储ASCII码表示的十进制数
DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE,DS:DATA,SS:SSTACK

START:  MOV AX,DATA ; 将数据段地址加载到AX寄存器
        MOV DS,AX ; 将数据段地址存入DS寄存器
        MOV AX,SSTACK ; 将栈段地址加载到AX寄存器
        MOV SS,AX ; 将栈段地址存入SS寄存器
        MOV AX,OFFSET SADD ; 将SADD的偏移地址加载到AX寄存器
        MOV SI,AX ; 将AX寄存器的值存入SI寄存器
        MOV BX,0010H ; 将十六进制数0F存入BX寄存器
        MOV CX,0003H ; 将十六进制数04存入CX寄存器
        MOV AH,00H ; 清空AH寄存器
        MOV AL,[SI] ; 将SI指向的内存单元的值加载到AL寄存器
        CMP AL,40H ; 比较AL寄存器的值与40H
        JL T1 ; 如果小于40H，跳转到标签T1
        SUB AL,07H ; AL寄存器减去07H
T1:     SUB AL,30H ; AL寄存器减去30H
A1:     IMUL BX ; 无符号乘法，将AX与BX相乘
        MOV DL,[SI+01] ; 将SI+1指向的内存单元的值加载到DX寄存器
        AND DX,00FFH ; 将DX寄存器与00FFH进行按位与运算
        ADC AX,DX ; 将DX寄存器的值与AX寄存器的值相加，包括进位
        CMP DX,40H ; 比较DX寄存器的值与40H
        JL T2 ; 如果小于40H，跳转到标签T2
        SUB AX,07H ; DX寄存器减去07H
T2:     SUB AX,30H ; AX寄存器减去30H
        INC SI ; SI寄存器加1
        LOOP A1 ; 循环执行标签A1，直到CX寄存器的值为0
A2:     JMP A2 ; 无条件跳转到标签A2

CODE	ENDS
        END START
