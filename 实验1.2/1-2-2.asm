;将十六位二进制数转换为ASCII码表示的十进制数
SSTACK  SEGMENT STACK        ; 定义一个名为SSTACK的堆栈段
        DW 64 DUP(?)           ; 堆栈段初始化为64个未初始化的字节
SSTACK  ENDS                ; 堆栈段定义结束

CODE    SEGMENT
        ASSUME CS:CODE

START:  MOV DX,0ABCH
        MOV SI, 3515H           ; 将SI寄存器设置为3515H
A1:     DEC SI                  ; 将SI寄存器减1
        MOV AX, DX              ; 将AX寄存器设置为DX的值
        MOV DX, 0000H           ; 将DX寄存器设置为0000H
        MOV CX, 000AH           ; 将CX寄存器设置为000AH
        DIV CX                  ; 将AX寄存器的值除以CX寄存器的值，商存入AL，余数存入AH
        XCHG AX, DX             ; 交换AX和DX寄存器的值
        ADD AL, 30H             ; 将AL寄存器的值加上30H
        MOV [SI], AL            ; 将AL寄存器的值存入[SI]的位置
        CMP DX, 0000H           ; 比较DX寄存器的值和0000H
        JNE A1                  ; 如果不相等，则跳转到标签A1
A2:     CMP SI, 3510H           ; 比较SI寄存器的值和3515H
        JZ A3                  ; 如果不相等，则跳转到标签A3
        DEC SI                  ; 将SI寄存器减1
        MOV AL, 30H             ; 将AL寄存器设置为30H
        MOV [SI], AL            ; 将AL寄存器的值存入[SI]的位置
        JMP A2                  ; 无条件跳转到标签A2
A3:     MOV AX, 4C00H           ; 将AX寄存器设置为4C00H
        INT 21H                 ; 调用21H中断
CODE    ENDS                   ; 代码段定义结束
        END START
