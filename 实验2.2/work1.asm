;=========================================================
; 文件名: work1
; 功能描述: 8254产生计时显示流水灯
;=========================================================

IOY1     EQU  0640H;IOY1起始地址
IOY0     EQU  0600H;IOY0起始地址
MY8255_A    EQU  IOY1+00H*2
MY8255_B    EQU  IOY1+01H*2
MY8255_C    EQU  IOY1+02H*2
MY8255_MODE  EQU  IOY1+03H*2

A8254    EQU  06C0H
B8254    EQU  06C2H
C8254    EQU  06C4H
CON8254  EQU  06C6H

SSTACK	SEGMENT STACK
		DW 32 DUP(?)
SSTACK	ENDS

CODE	SEGMENT
		ASSUME CS:CODE, SS:SSTACK
START:	PUSH DS
		MOV AX, 0000H
		MOV DS, AX
		MOV AX, OFFSET IRQ7			;取中断入口地址
		MOV SI, 003CH				;中断矢量地址
		MOV [SI], AX				;填IRQ7的偏移矢量
		MOV AX, CS					;段地址
		MOV SI, 003EH
		MOV [SI], AX				;填IRQ7的段地址矢量
		CLI
		POP DS
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
		;8255

    	MOV DX, 0606H
		MOV AL, 80H
		OUT DX, AL
		MOV BX, 8001H

		;8254
		MOV DX, CON8254
		MOV AL, 36H				;计数器0，方式3
		OUT DX, AL

		MOV DX, A8254			;低8位
		MOV AL, 0E8H
		OUT DX, AL
		MOV AL, 03H				;高8位
		OUT DX, AL

		MOV DX, CON8254
		MOV AL, 76H				;计数器1，方式3
		OUT DX, AL

		MOV DX, B8254			;低8位
		MOV AL, 0E8H
		OUT DX, AL
		MOV AL, 03H				;高8位
		OUT DX, AL
		STI
AA1:    JMP AA1
IRQ7:	MOV DX, 0600H
		MOV AL, BH
		OUT DX, AL
		ROR BH, 1

		MOV DX, 0602H
		MOV AL, BL
		OUT DX, AL
		ROL BL, 1
T1:		MOV AL, 20H
		OUT 20H, AL				;中断结束命令
		IRET
CODE	ENDS
		END  START
