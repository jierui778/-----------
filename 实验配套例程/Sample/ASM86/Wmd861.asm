;========================================================
; �ļ���:   Wmd861.Asm
; ��������: ת������
;========================================================
; ʵ��Ŀ��: ��ʵ��Ϊϵͳ��ʶʵ�飬Ŀ������ͨ����ʵ����
;           ѧϰʵ��ϵͳ��ʹ�á�
;========================================================

SSTACK	SEGMENT STACK				;�����ջ��
		DW 32 DUP(?)
SSTACK	ENDS

CODE	SEGMENT
		ASSUME CS:CODE, SS:SSTACK
START:	PUSH DS
        XOR DX,DX
	 	XOR AX, AX
		MOV DS, AX
		MOV SI, 3504H				;����������ʼ��ַ
		MOV CX, 5					;ѭ������
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
		INT 21H						;������ֹ
CODE	ENDS
		END START
	