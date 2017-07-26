;*************************************************************
;Assemble Code 
;*************************************************************
.MODEL SMALL
.DATA
	n	dw	0
	count	dw	0
.STACK
.CODE
.STARTUP
           PUSH BX
           PUSH AX
           MOV BX,0
AGAIN1: MOV AH,1
           INT 21H
           CMP AL,13
           JZ NEXT1
           SUB AL,30H
           MOV AH,0
           PUSH AX
           MOV AX,10
           MUL BX
           MOV BX,AX
           POP AX
           ADD BX,AX
           JMP AGAIN1

NEXT1: MOV n,BX
           POP AX
           POP BX


           MOV AH,2
           MOV DL,13
           INT 21H
           MOV AH,2
           MOV DL,10
           INT 21H
           CMP n,1
           JB T1

           JMP T2

T1:             PUSH AX
           MOV AX,520
           MOV n,AX
           POP AX

T2:  
           MOV AH,2
           MOV DL,13
           INT 21H
           MOV AH,2
           MOV DL,10
           INT 21H
           MOV AX,n
           MOV BX,10
  LP1: CWD
           DIV BX
           PUSH DX
           INC COUNT
           CMP AX,0
           JNE LP1
 PRINT1: POP DX
           ADD DX,30H
           MOV AH,2
           INT 21H
           DEC COUNT
           JNE PRINT1

.EXIT 0
          END