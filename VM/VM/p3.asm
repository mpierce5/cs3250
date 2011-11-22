SIZE .INT 7
cnt .INT 0
tenth .INT 0
c	.BYT 1
	.BYT 1
	.BYT 1
	.BYT 1
	.BYT 1
	.BYT 1
	.BYT 1
data .INT 0
flag .INT 0
opdv .INT 0
zero .INT 0
one	.INT 1
i	.INT 0
temp .INT 0
dec  .INT -1
char_zero .BYT 48
char_one	.BYT 49
char_two	.BYT 50
char_three	.BYT 51
char_four	.BYT 52
char_five	.BYT 53
char_six	.BYT 54
char_seven	.BYT 55
char_eight	.BYT 56
char_nine	.BYT 57
ten		.INT 10
newline .BYT 10
char_N	.BYT 78
char_u	.BYT 117
char_m	.BYT 109
char_b	.BYT 98
char_e	.BYT 101
char_r	.BYT 114
char_space	.BYT 32
char_t	.BYT 116
char_o	.BYT 111
char_O	.BYT 79
char_B	.BYT 66
char_i	.BYT 105
char_g	.BYT 103
char_@	.BYT 64
char_+	.BYT 43
char_-	.BYT 45
char_s	.BYT 115
char_n	.BYT 110
char_a	.BYT 97
char_p	.BYT 112
char_d	.BYT 100

//main function goes here
//Get input from the keyboard until the symbol ‘@’ is encountered.
//Convert the char data input from the keyboard to an integer be
//Sure to account for the sign of the number.  If no sign is used
//always assume the number is positive.

main LDR R0, one
LDR R1, zero
LDR R2, zero
LDR R3, zero
LDA R9, retFrReset1
JMP reset

//create a label that reset can jump back to
retFrReset1 LDA R9, retFrGetData

//on return c will have the data retrieved
JMP getdata

//*******************
//check c[0] for a stop symbol
retFrGetData MOV R8, R0
LDB R2, char_@
LDB R1, c
CMP R1, R2
BRZ R1, FINISH

//check for '+'
LDB R2, char_+
LDB R1, c
CMP R1, R2
BNZ R1, CHECKFORMINUS
JMP OPFOUND

//check for 'minus'
CHECKFORMINUS LDB R2, char_-
LDB R1, c
CMP R1, R2
BNZ R1, ADDSIGN
JMP OPFOUND

//if '+', OR '-' found, get next digit
OPFOUND LDA R9, RET_OP_FOUND
JMP getdata

RET_OP_FOUND JMP PROCESSLOOP
MOV R8, R0
//ld address of c in R1
ADDSIGN  MOV R8, R0
LDA R1, c
//ld value of c in R0
LDB R0, c
//increment pointer to next char by adding 1 to R1
ADI R1, 1
//store address of pointer in temp
STR R1, temp
//store value in R0, in address in temp
STB R0, *temp
//store '+' in c[0]
LDB R0, char_+
STB R0, c
LDR R0, cnt
ADI R0, 1
STR R0, cnt
MOV R0, R8

//continue looping until all values are stored in array
PROCESSLOOP MOV R8, R0
LDR R1, data
BRZ R1, FINISH
LDB R4, newline
CMP R8, R4
BRZ R8, NEWLINEFOUND
//store value read from console in char array
LDA R9, PROCESSLOOP
JMP getdata

NEWLINEFOUND LDR R0, zero
STR R0, data
ADI R0, 1
STR R0, tenth
LDR R0, cnt
LDR R1, dec
ADD R0, R1
ADD R0, R1
STR R0, cnt

OPDLOOP LDR R1, flag
BNZ R1, FLAGGED
LDR R1, cnt
BRZ R1, FLAGGED
//compute a number
LDA R1, c
LDR R2, tenth
LDR R3, cnt
ADD R3, R1
STR R3, temp
LDB R3, *temp
LDA R9, RETOPDV
LDB R1, c
JMP opd

RETOPDV LDR R0, cnt
LDR R1, dec
ADD R0, R1
STR R0, cnt
LDR R0, tenth
LDR R1, ten
MUL R0, R1
STR R0, tenth
JMP OPDLOOP

FLAGGED LDR R0, flag
BNZ R0, RESETALL
LDB R0, char_O
TRP 3
LDB R0, char_p
TRP 3
LDB R0, char_e
TRP 3
LDB R0, char_r
TRP 3
LDB R0, char_a
TRP 3
LDB R0, char_n
TRP 3
LDB R0, char_d
TRP 3
LDB R0, char_space
TRP 3
LDB R0, char_i
TRP 3
LDB R0, char_s
TRP 3
LDB R0, char_space
TRP 3
LDR R0, opdv
TRP 1
LDB R0, newline
TRP 3

RESETALL JMP main


FINISH TRP 4 
TRP 3
TRP 0

//R1 - C[0]
//R2 - tenth
//R3 - C[cnt]
//******opd function*****************************
opd LDR R4, zero
LDB R0, char_zero
CMP R0, R3
BNZ R0, TESTONE
ADI R4, 0
JMP FLAGTEST

TESTONE LDB R0, char_one
CMP R0, R3
BNZ R0, TESTTWO
ADI R4, 1
JMP FLAGTEST

TESTTWO LDB R0, char_two
CMP R0, R3
BNZ R0, TESTTHREE
ADI R4, 2
JMP FLAGTEST

TESTTHREE LDB R0, char_three
CMP R0, R3
BNZ R0, TESTFOUR
ADI R4, 3
JMP FLAGTEST

TESTFOUR LDB R0, char_four
CMP R0, R3
BNZ R0, TESTFIVE
ADI R4, 4
JMP FLAGTEST

TESTFIVE LDB R0, char_five
CMP R0, R3
BNZ R0, TESTSIX
ADI R4, 5
JMP FLAGTEST

TESTSIX LDB R0, char_six
CMP R0, R3
BNZ R0, TESTSEVEN
ADI R4, 6
JMP FLAGTEST

TESTSEVEN LDB R0, char_seven
CMP R0, R3
BNZ R0, TESTEIGHT
ADI R4, 7
JMP FLAGTEST

TESTEIGHT LDB R0, char_eight
CMP R0, R3
BNZ R0, TESTNINE
ADI R4, 8
JMP FLAGTEST

TESTNINE LDB R0, char_nine
CMP R0, R3
BNZ R0, NOT_A_NUMBER
ADI R4, 9
JMP FLAGTEST

FLAGTEST LDR R0, flag
BNZ R0, ENDOFTESTS
LDB R0, char_+
CMP R0, R1
BNZ R0, FLAGTESTMINUS

LDR R2, tenth
MUL R4, R2
LDR R6, opdv
ADD R4, R6
STR R4, opdv
JMR R9

FLAGTESTMINUS LDR R6, dec
MUL R4, R6
LDR R2, tenth
MUL R4, R2
LDR R6, opdv
ADD R4, R6
STR R4, opdv

ENDOFTESTS JMR R9 

NOT_A_NUMBER MOV R0, R3
TRP 3
LDB R0, char_space
TRP 3
LDB R0, char_i
TRP 3
LDB R0, char_s
TRP 3
LDB R0, char_space
TRP 3
LDB R0, char_n
TRP 3
LDB R0, char_o
TRP 3
LDB R0, char_t
TRP 3
LDB R0, char_space
TRP 3
LDB R0, char_a
TRP 3
LDB R0, char_space
TRP 3
LDB R0, char_n
TRP 3
LDB R0, char_u
TRP 3
LDB R0, char_m
TRP 3
LDB R0, char_b
TRP 3
LDB R0, char_e
TRP 3
LDB R0, char_r
TRP 3
LDB R0, newline
TRP 3
LDR R0, one
STR R0, flag
JMR R9





//******reset function*****************************
//R0 - data
//R1 - opdv
//R2 - cnt
//R3 - flag
//R9 - return address
//*************************************************
reset LDR R5, zero
LDR R7, zero
STR R7, i
LDR R6, SIZE
LDA R4, c
STR R4, temp
//store address of location in array in R4
//set all values to 0
RESETLOOP STB R7, *temp
//increment R4(pointer to array) and R5 (index)
ADI R4, 1
ADI R5, 1
STR R4, temp
STR R5, i
CMP R5, R6
BRZ R5, ENDRESET
LDR R5, i
JMP RESETLOOP

ENDRESET STR R0, data
STR R1, opdv
STR R2, cnt
STR R3, flag
JMR R9

//R0 - data
//R1 - cnt
//R2 - SIZE
//R3 - iterator
//R4 - temp reg
//R5 - char array pointer
//******getdata function***************************
getdata LDR R1, cnt
LDR R2, SIZE
LDR R3, cnt
LDA R5, c
//add offset to get correct spot in the array
ADD R5, R3
STR R5, temp

MOV R4, R3
//compare iterator with size
CMP R4, R2
BRZ R4, PRINTFAIL
TRP 4
//increment cnt
STB R0, *temp
ADI R3, 1
STR R3, cnt
JMP FINISHEDGETDATA

PRINTFAIL LDB R0, char_N
TRP 3
LDB R0, char_u
TRP 3
LDB R0, char_m
TRP 3
LDB R0, char_b
TRP 3
LDB R0, char_e
TRP 3
LDB R0, char_r
TRP 3
LDB R0, char_space
TRP 3
LDB R0, char_t
TRP 3
LDB R0, char_o
TRP 3
TRP 3
LDB R0, char_space
TRP 3
LDB R0, char_B
TRP 3
LDB R0, char_i
TRP 3
LDB R0, char_g
TRP 3
LDB R0, newline
TRP 3

STR R9, temp
LDA R9, RETFLUSH
JMP flush
RETFLUSH LDR R9, temp

FINISHEDGETDATA JMR R9


//******flush function*****************************
flush LDB R4, *temp
LDR R0, zero
STR R0, data
LDB R6, newline
//search for newline character
FLUSHLOOP TRP 4
STB R0, c
CMP R0, R6
BRZ R0, ENDFLUSH
JMP FLUSHLOOP

ENDFLUSH JMR R9




















