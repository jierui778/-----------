;========================================================
; 文件名:   Wmd861.Asm
; 功能描述: 转换代码
;========================================================
; 实验目的: 本实验为系统认识实验，目的在于通过该实验来
;           学习实验系统的使用。
;========================================================

SSTACK	SEGMENT STACK				;定义堆栈段
		DW 32 DUP(?)
SSTACK	ENDS

CODE	SEGMENT
		ASSUME CS:CODE, SS:SSTACK
START:	PUSH DS
        XOR DX,DX
	 	XOR AX, AX
		MOV DS, AX
		MOV SI, 3504H				;建立数据起始地址
		MOV CX, 5					;循环次数
     	MOV BL,0AH
     	MOV AX,000CH
        
AA1:    DIV BL
        ADD AH,30H
        MOV [SI],AH
        XOR AH,AH 
        DEC SI											
		LOOP AA1
		
		MOV [SI],AH
		MOV AX,4C00H
		INT 21H						;程序终止
CODE	ENDS
		END START
	