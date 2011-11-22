c	.BYT 99
a	.BYT 97
t	.BYT 116
s	.BYT 115
minus	.BYT 45
equals	.BYT 61
SIZE .INT 10
ARR .INT 10
	.INT 2
	.INT 3
	.INT 4
	.INT 15
	.INT -6
	.INT 7
	.INT 8
	.INT 9
	.INT 10
i 	.INT 0
sum	.INT 0
temp .INT 0
result .INT 0
DIVBY2 .INT 2
I	.BYT 105
space .BYT 32
e	.BYT 101
v	.BYT 118
n	.BYT 110
o	.BYT 111
d	.BYT 100
newLine .BYT 10
S	.BYT 83
u	.BYT 117
m	.BYT 109

LDA R1, ARR
STR R1, temp

LDR R0, sum
LDR R2, i
WHILELOOP LDR R3, *temp
ADD R0, R3
ADI R1, 4
STR R1, temp
ADI R2, 1
MOV R6, R3
MOV R7, R3
LDR R8, DIVBY2
DIV R6, R8
MUL R6, R8
CMP R6, R7
BRZ R6, EVEN
BNZ R6, ODD
CONTINUE MOV R6, R2
LDR R4, SIZE
CMP R6, R4
BRZ R6, FINISHED
JMP WHILELOOP

EVEN MOV R9, R0
MOV R0, R3 
TRP 1
LDB R0, space
TRP 3
LDB R0, I
TRP 3
LDB R0, s
TRP 3
LDB R0, space
TRP 3
LDB R0, e
TRP 3
LDB R0, v
TRP 3
LDB R0, e
TRP 3
LDB R0, n
TRP 3
LDB R0, newLine
TRP 3
MOV R0, R9
JMP CONTINUE

ODD MOV R9, R0
MOV R0, R3 
TRP 1
MOV R8, R0
LDB R0, space
TRP 3
LDB R0, I
TRP 3
LDB R0, s
TRP 3
LDB R0, space
TRP 3
LDB R0, o
TRP 3
LDB R0, d
TRP 3
TRP 3
LDB R0, newLine
TRP 3
MOV R0, R9
JMP CONTINUE

FINISHED MOV R9, R0
LDB R0, S
TRP 3
LDB R0, u
TRP 3
LDB R0, m
TRP 3
LDB R0, space
TRP 3
LDB R0, I
TRP 3
LDB R0, s
TRP 3
LDB R0, space
TRP 3
MOV R0, R9
TRP 1
LDB R0, newLine
TRP 3
LDB R0, newLine
TRP 3

LDB R0, c
TRP 3
LDB R0, a
TRP 3
LDB R0, t
TRP 3
LDB R0, s
TRP 3
LDB R0, space
TRP 3
LDB R0, newLine
TRP 3

LDA R0, c
STR R0, temp
LDR R0, *temp 
TRP 1
MOV R8, R0
LDB R0, space
TRP 3
LDB R0, newLine
TRP 3

LDB R0, c
LDB R1, t
STB R0, t
STB R1, c

LDA R0, t
STR R0, temp
LDR R0, *temp 
TRP 1
MOV R7, R0
LDB R0, newLine
TRP 3

LDB R0, t
TRP 3
LDB R0, a
TRP 3
LDB R0, c
TRP 3
LDB R0, s
TRP 3
LDB R0, space
TRP 3
LDB R0, minus
TRP 3
LDB R0, space
TRP 3
LDB R0, c
TRP 3
LDB R0, a
TRP 3
LDB R0, t
TRP 3
LDB R0, s
TRP 3
LDB R0, space
TRP 3
LDB R0, equals
TRP 3
LDB R0, space
TRP 3
MOV R0, R8
SUB R0, R7
TRP 1
LDB R0, newLine
TRP 3
TRP 0













































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





else if(execInstr.OpCode == 11)
		{

			int destReg = execInstr.DestReg;
			int label = execInstr.label;
			int value = charByteCode[label];
			//cout << "executing instruction: Dest reg = " << execInstr.DestReg << " label: " << execInstr.label << "\n";
			Registers[destReg] = value;

		}



























