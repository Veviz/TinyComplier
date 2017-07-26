;*************************************************************
;Assemble Code 
;*************************************************************
.MODEL SMALL
.DATA
	n	dw	0
	Z1	dw	0
	Z2	dw	0
	m	dw	0
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
           CMP n,0
           JA T1

           JMP T2

T1:             PUSH AX
           MOV AX,n
           ADD AX,10
           MOV Z1,AX
           POP AX

           PUSH AX
           MOV AX,Z1
           MOV n,AX
           POP AX

           JMP T3

T2:             PUSH AX
           MOV AX,n
           ADD AX,20
           MOV Z2,AX
           POP AX

           PUSH AX
           MOV AX,Z2
           MOV n,AX
           POP AX

T3:  
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
           PUSH BX
           PUSH AX
           MOV BX,0
AGAIN2: MOV AH,1
           INT 21H
           CMP AL,13
           JZ NEXT2
           SUB AL,30H
           MOV AH,0
           PUSH AX
           MOV AX,10
           MUL BX
           MOV BX,AX
           POP AX
           ADD BX,AX
           JMP AGAIN2

NEXT2: MOV m,BX
           POP AX
           POP BX


           MOV AH,2
           MOV DL,13
           INT 21H
           MOV AH,2
           MOV DL,10
           INT 21H
           CMP m,10
           JA T4

           JMP T5

T4:             PUSH AX
           MOV AX,30
           MOV m,AX
           POP AX

           JMP T6

T5:             PUSH AX
           MOV AX,20
           MOV m,AX
           POP AX

T6:  
           MOV AH,2
           MOV DL,13
           INT 21H
           MOV AH,2
           MOV DL,10
           INT 21H
           MOV AX,m
           MOV BX,10
  LP2: CWD
           DIV BX
           PUSH DX
           INC COUNT
           CMP AX,0
           JNE LP2
 PRINT2: POP DX
           ADD DX,30H
           MOV AH,2
           INT 21H
           DEC COUNT
           JNE PRINT2

.EXIT 0
          END