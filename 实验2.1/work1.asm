A8254   EQU     IOY0+00H*2;宏定义端口地址
B8254   EQU     IOY0+01H*2;宏定义端口地址
C8254   EQU     IOY0+02H*2;宏定义端口地址
CON8254 EQU     IOY0+03H*2;控制寄存器地址地址

SSTACK  SEGMENT STACK;定义堆栈为32个字
        DB      32 DUP(0)

CODE    SEGMENT
        ASSUME  CS:CODE,SS:SSTACK

START:  PUSH    DS
        MOV     AX,0000H
        MOV     DS,AX;标准模式下DS=0
        MOV     AX,OFFSET IRQ7  ;取中断入口地址
        MOV     SI,003CH    ;中断矢量地址
        MOV     [SI],AX;将中断入口地址送中断矢量表
        MOV     AX,CS      ;取段地址
        MOV     SI,003EH    ;中断矢量地址
        MOV     [SI],AX;将段地址送中断矢量表
        CLI             ;关中断
        POP     DS    ;恢复DS
        MOV     AL,11H;设置8254控制字
        OUT     20H,AL;写入8259A控制字
        MOV     AL,08H;设置8254控制字
        OUT     21H,AL;写入8259A控制字
        MOV     AL,04H;设置8254控制字
        OUT     21H,AL;写入8259A控制字
        MOV     AL,01H;设置8254控制字
        OUT     21H,AL;写入8259A控制字
        MOV     AL,6FH;设置8254控制字
        OUT     21H,AL;写入8259A控制字
        MOV     DX,CON8254;8254初始化,写入控制寄存器
        MOV     AL,10H;计数器0,方式0,16位计数器
        OUT     DX,AL;写入控制寄存器
        MOV     AL,A8254;写入计数器0低字节
        MOV     AL,04H;写入计数器0低字节
        OUT     DX,AL;写入初值
        STI             ;开中断
AA1:    JMP     AA1;死循环

IRQ7:   MOV     DX,A8254
        MOV     AL,04H
        MOV     DX,AL;重新写入初值
        MOV     AX,014DH
        INT     10H;显示字符M
        MOV     AX,0120H
        INT     10H;显示字符空格
        MOV     AL,20H
        OUT     20H,AL;中断结束
        IRET            ;中断返回
CODE    ENDS
        END     START
