c	.BYT 99
a	.BYT 97
t	.BYT 116
s	.BYT 115
minus	.BYT 45
equals	.BYT 61
newLine .BYT 10
space .BYT 32

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

LDA R0, temp
STR R0, *temp
LDR R0, temp 
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

LDA R0, temp
STR R0, *temp
LDR R0, temp 
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
LDB R0, minus
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