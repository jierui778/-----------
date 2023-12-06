;Lcd.asm
;LCD显示设计实验

INCLUDE LCD.INC


IOY0         EQU   0600H          ;片选IOY0对应的端口始地址
MY8255_A     EQU   IOY0+00H*2     ;8255的A口地址
MY8255_B     EQU   IOY0+01H*2     ;8255的B口地址
MY8255_C     EQU   IOY0+02H*2     ;8255的C口地址
MY8255_MODE  EQU   IOY0+03H*2     ;8255的控制寄存器地址

STACK1 SEGMENT STACK
        DW 256 DUP(?)
STACK1 ENDS

DATA SEGMENT 
CMD   DB   ?                      ;定义操作LCD命令变量
DAT   DB   ?                      ;定义操作LCD数据变量
XAD   DB   ?                      ;定义X地址变量
YAD   DB   ?                      ;定义Y地址变量
DATA ENDS

CODE SEGMENT
        ASSUME CS:CODE,DS:DATA

START: MOV AX,DATA
       MOV DS,AX

       MOV DX,MY8255_MODE         ;定义8255工作方式            
       MOV AL,80H                 ;工作方式0，A口和B口为输出
       OUT DX,AL
             
       MOV CMD,04H                ;设置第一块显示打开
       MOV DAT,3FH
       CALL WRITE

       MOV CMD,08H                ;设置第二块显示打开
       MOV DAT,3FH
       CALL WRITE

       MOV CMD,04H                ;设置第一块起始行
       MOV DAT,0C0H
       CALL WRITE

       MOV CMD,08H                ;设置第二块起始行
       MOV DAT,0C0H
       CALL WRITE
 
       MOV AL,0
CLRALL:MOV CMD,04H                ;清屏
       CALL CLEAR
       MOV CMD,08H
       CALL CLEAR
       INC AL
       CMP AL,8
       JNZ CLRALL

       MOV XAD,0BAH               ;在第一块、以X地址BAH
       MOV YAD,40H                ;Y地址40H为起始 
       MOV CMD,04H                
       MOV SI,OFFSET TANG         ;显示汉字“唐”
       CALL WRITEHZ

       MOV XAD,0BAH               ;在第一块、以X地址BAH
       MOV YAD,50H                ;Y地址50H为起始
       MOV CMD,04H
       MOV SI,OFFSET DU           ;显示汉字“都”
       CALL WRITEHZ
       
       MOV XAD,0BAH               ;在第一块、以X地址BAH
       MOV YAD,60H                ;Y地址60H为起始
       MOV CMD,04H
       MOV SI,OFFSET KE           ;显示汉字“科”
       CALL WRITEHZ
       
       MOV XAD,0BAH		          ;在第一块、以X地址BAH	
       MOV YAD,70H                ;Y地址70H为起始
       MOV CMD,04H
       MOV SI,OFFSET JIAO         ;显示汉字“教”
       CALL WRITEHZ
       
       MOV XAD,0BAH               ;在第二块、以X地址BAH
       MOV YAD,40H                ;Y地址40H为起始
       MOV CMD,08H
       MOV SI,OFFSET YI           ;显示汉字“仪”
       CALL WRITEHZ
       
       MOV XAD,0BAH               ;在第二块、以X地址BAH     
       MOV YAD,50H                ;Y地址50H为起始
       MOV CMD,08H
       MOV SI,OFFSET QI           ;显示汉字“器”
       CALL WRITEHZ
       
       MOV XAD,0BAH               ;在第二块、以X地址BAH
       MOV YAD,60H                ;Y地址60H为起始
       MOV CMD,08H
       MOV SI,OFFSET GONG         ;显示汉字“公”
       CALL WRITEHZ
       
       MOV XAD,0BAH               ;在第二块、以X地址BAH
       MOV YAD,70H                ;Y地址70H为起始
       MOV CMD,08H
       MOV SI,OFFSET SI1          ;显示汉字“司”
       CALL WRITEHZ

       MOV XAD,0BCH               ;在第一块、以X地址BCH
       MOV YAD,60H                ;Y地址60H为起始
       MOV CMD,04H
       MOV SI,OFFSET HUAN         ;显示汉字“欢”
       CALL WRITEHZ
       
       MOV XAD,0BCH               ;在第一块、以X地址BCH
       MOV YAD,70H                ;Y地址70H为起始
       MOV CMD,04H
       MOV SI,OFFSET YING         ;显示汉字“迎”
       CALL WRITEHZ
       
       MOV XAD,0BCH               ;在第二块、以X地址BCH
       MOV YAD,40H                ;Y地址40H为起始
       MOV CMD,08H
       MOV SI,OFFSET NIN          ;显示汉字“您”
       CALL WRITEHZ
       
       MOV XAD,0BCH               ;在第二块、以X地址BCH
       MOV YAD,50H                ;Y地址50H为起始
       MOV CMD,08H
       MOV SI,OFFSET GANTAN       ;显示标点“！”
       CALL WRITEHZ
     
MOVE1: MOV CX,0C0H                ;设置起始行从C0H到FFH
MOVE2: MOV DAT,CL                 ;达到显示向上移动的效果
       MOV CMD,04H
       CALL WRITE
       MOV CMD,08H
       CALL WRITE
       CALL DALLY
       
       MOV AH,1                   ;判断是否有按键按下
       INT 16H
       JNZ QUIT                   ;无按键则继续循环，有则退出
       
       INC CX
       CMP CX,100H
       JNZ MOVE2
       JMP MOVE1
       
QUIT:  CALL LEDOFF
       MOV AX,4C00H               ;结束程序退出
       INT 21H

WRITE PROC NEAR                   ;写命令和数据子程序
       MOV DX,MY8255_B            ;送出命令或数据
       MOV AL,DAT       
       OUT DX,AL

       OR  CMD,10H                ;使E信号产生高脉冲，将命令或数据写入
       MOV AL,CMD
       MOV DX,MY8255_A
       OUT DX,AL
       AND CMD,0EFH
       MOV AL,CMD
       OUT DX,AL      
       RET
WRITE ENDP

CLEAR PROC NEAR                   ;清X地址为B8H～BFH中的一页屏幕子程序
       PUSH AX
       ADD AL,0B8H                
       MOV DAT,AL                 ;设置X地址
       CALL WRITE
       CALL QUERY

       MOV DAT,40H                ;设置Y地址
       CALL WRITE
       CALL QUERY

       MOV CX,64                  ;循环64次，清除整页
LC:    MOV DAT,00H                ;向数据单元中写00H，达到清屏   
       ADD CMD,2
       CALL WRITE                 
       SUB CMD,2
       CALL QUERY
       LOOP LC

       POP AX
       RET
CLEAR ENDP

QUERY PROC NEAR                   ;查询LCD控制器是否空闲
       ADD CMD,1
       MOV DX,MY8255_MODE         ;设置8255的B口为输入，需要读数据
       MOV AL,82H
       OUT DX,AL

Q1:    OR  CMD,10H                ;将命令送入
       MOV AL,CMD
       MOV DX,MY8255_A
       OUT DX,AL
       AND CMD,0EFH
       MOV AL,CMD
       OUT DX,AL      

       MOV DX,MY8255_B            ;读出查询字，进行判断
       IN  AL,DX
       TEST AL,80H                
       JZ  Q2                     ;空闲则退出，否则继续查询 
       JMP Q1

Q2:    MOV DX,MY8255_MODE         ;恢复8255控制字，A、B口均为输出
       MOV AL,80H
       OUT DX,AL
       SUB CMD,1
       RET
QUERY ENDP

WRITEHZ PROC NEAR                 ;从某一坐标为起始写汉字子程序
       MOV BL,0                   ;将16*16分成两个16*8完成写入 

WRHZ1: MOV AL,XAD                 ;设置X坐标
       MOV DAT,AL
       CALL WRITE
       CALL QUERY
       
       MOV AL,YAD                 ;设置Y坐标
       MOV DAT,AL
       CALL WRITE
       CALL QUERY
       
       MOV CX,0                   
WRHZ2: MOV DI,SI                  ;装入汉字点阵数据起始地址
       MOV AL,BL                  ;计算偏移[CX+(BL*16)]
       MOV DL,16
       MUL DL
       ADD AX,CX
       ADD DI,AX                  ;将结果与起始地址相加
       MOV AL,BYTE PTR[DI]        ;取出数据并写入LCD
       MOV DAT,AL
       ADD CMD,2
       CALL WRITE
       SUB CMD,2
       CALL QUERY
       INC CX
       CMP CX,16
       JNZ WRHZ2                  ;未写完则跳回继续
       
       ADD XAD,1                  ;X地址加1，准备写下页
       INC BL
       CMP BL,2
       JNZ WRHZ1

       RET
WRITEHZ ENDP

LEDON PROC NEAR                   ;打开背景灯
       OR  CMD,20H
       MOV DX,MY8255_A
       MOV AL,CMD
       OUT DX,AL
       RET
LEDON ENDP

LEDOFF PROC NEAR                  ;关闭背景灯
       AND CMD,0DFH
       MOV DX,MY8255_A
       MOV AL,CMD
       OUT DX,AL
       RET
LEDOFF ENDP

DALLY PROC NEAR                   ;软件延时子程序
       PUSH CX
       PUSH AX
       MOV CX,0000H
D1:    MOV AX,0001H
D2:    DEC AX
       JNZ D2
       LOOP D1
       POP AX
       POP CX
       RET
DALLY ENDP

CODE ENDS
     END START
