SSTACK SEGMENT STACK
           DW 64 DUP(?)
SSTACK ENDS

CODE      SEGMENT
          ASSUME CS:CODE
START:    MOV    AX, DATA
          MOV    DS, AX
          MOV    AX, OFFSET SADD
          MOV    SI, AX
          MOV    BX, 000AH
          MOV    CX, 0004H
          MOV    AH, 00H
          MOV    AL, [SI]
          SUB    AL, 30H
A1:       IMUL   BX
          MOV    DX, [SI+01]
          AND    DX, 00FFH
          ADC    AX, DX
          SBB    AX, 30H
          INC    SI
          LOOP   A1
A2:       JMP    A2
CODE ENDS
END START
; MOV AX,11H
; MOV BX,66H; FILEPATH: /D:/masm/hello.asm

; .MODEL SMALL
; .STACK 100H

; .DATA
;     MESSAGE DB 'Hello, World!', '$'

; .CODE
;     MAIN PROC
;         MOV AX, @DATA
;         MOV DS, AX

;         MOV AH, 09H
;         MOV DX, OFFSET MESSAGE
;         INT 21H

;         MOV AH, 4CH
;         INT 21H
;     MAIN ENDP

; END MAIN
