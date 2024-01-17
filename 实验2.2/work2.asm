;=========================================================
; 文件名: work2.asm
; 功能描述: 8254每隔0.1秒自动产生中断
;=========================================================

A8254    EQU  06C0H
B8254    EQU  06C2H
C8254    EQU  06C4H
CON8254  EQU  06C6H

IOY0         EQU   0600H          ;片选IOY0对应的端口始地址
MY8255_A     EQU   IOY0+00H*2     ;8255的A口地址
MY8255_B     EQU   IOY0+01H*2     ;8255的B口地址
MY8255_C     EQU   IOY0+02H*2     ;8255的C口地址
MY8255_MODE  EQU   IOY0+03H*2     ;8255的控制寄存器地址

STACK1 	SEGMENT STACK
        DW 256 DUP(?)
STACK1 	ENDS
CODE 	SEGMENT
        ASSUME CS:CODE
START: 	MOV DX,MY8255_MODE         ;初始化8255工作方式
       	MOV AL,86H                 ;工作方式1，A口输出，B口输入
       	OUT DX,AL
       	MOV DX,MY8255_MODE         ;C口PC2置位
       	MOV AL,05H
       	OUT DX,AL
		PUSH DS
		MOV AX, 0000H
		MOV DS, AX
		MOV AX, OFFSET MIR7			;取中断入口地址
		MOV SI, 003CH				;中断矢量地址
		MOV [SI], AX				;填IRQ7的偏移矢量
		MOV AX, CS					;段地址
		MOV SI, 003EH
		MOV [SI], AX				;填IRQ7的段地址矢量
		CLI
		POP DS


		;8254
		MOV DX, CON8254			;8254
		MOV AL, 36H				;计数器0，方式3
		OUT DX, AL
		MOV DX, A8254
		MOV AL, 0E8H
		OUT DX, AL
		MOV AL, 03H
		OUT DX, AL

		MOV DX, CON8254			;8254
		MOV AL, 76H				;计数器1，方式3
		OUT DX, AL
		MOV DX, B8254
		MOV AL, 0E8H
		OUT DX, AL
		MOV AL, 03H
		OUT DX, AL

		;初始化主片8259
		MOV AL, 11H
		OUT 20H, AL				;ICW1
		MOV AL, 08H
		OUT 21H, AL				;ICW2
		MOV AL, 04H
		OUT 21H, AL				;ICW3
		MOV AL, 01H
		OUT 21H, AL				;ICW4
		MOV AL, 6FH				;OCW1
		OUT 21H, AL
		STI
AA1:	NOP
		JMP AA1
MIR7:  	PUSH AX
       	MOV DX,MY8255_B            ;读B口
       	IN  AL,DX
       	MOV DX,MY8255_A            ;写A口
       	OUT DX,AL
	   	MOV AL,20H
       	OUT 20H,AL
       	POP AX
       	IRET
DELAY:	PUSH CX
		MOV CX, 0F00H
AA0:	PUSH AX
		POP  AX
		LOOP AA0
		POP CX
		RET
CODE 	ENDS
     	END START
