A1 .INT 1
A2 .INT 2
A3 .INT 3
A4 .INT 4
A5 .INT 5
A6 .INT 6
B300 .INT 300
B150 .INT 150
B50 .INT 50
B20 .INT 20
B10 .INT 10
B5 .INT 5
C500 .INT 500
C2 .INT 2
C5 .INT 5
C10 .INT 10
SPACE .BYT 32
NAMEM .BYT 77
NAMEi .BYT 105
NAMEc .BYT 99
NAMEh .BYT 104
NAMEa .BYT 97
NAMEe .BYT 101
NAMEl .BYT 108
NAMEP .BYT 80
NAMEr .BYT 114
NAMEc .BYT 99
NewLine .BYT 10
INTER .INT 0
FINAL .INT 0
LDB R0, NAMEM
TRP 3
LDB R0, NAMEi
TRP 3
LDB R0, NAMEc
TRP 3
LDB R0, NAMEh
TRP 3
LDB R0, NAMEa
TRP 3
LDB R0, NAMEe
TRP 3
LDB R0, NAMEl
TRP 3
LDB R0, SPACE
TRP 3
LDB R0, NAMEP
TRP 3
LDB R0, NAMEi
TRP 3
LDB R0, NAMEe
TRP 3
LDB R0, NAMEr
TRP 3
LDB R0, NAMEc
TRP 3
LDB R0, NAMEe
TRP 3
LDB R0, NewLine
TRP 3
LDR R0, B300
LDR R1, B150
ADD R0, R1
TRP 1
STR R0, INTER
LDB R0, SPACE
TRP 3
TRP 3
LDR R0, INTER
LDR R1, B50
ADD R0, R1
TRP 1
STR R0, INTER
LDB R0, SPACE
TRP 3
TRP 3
LDR R0, INTER
LDR R1, B20
ADD R0, R1
TRP 1
STR R0, INTER
LDB R0, SPACE
TRP 3
TRP 3
LDR R0, INTER
LDR R1, B10
ADD R0, R1
TRP 1
STR R0, INTER
LDB R0, SPACE
TRP 3
TRP 3
LDR R0, INTER
LDR R1, B5
ADD R0, R1
TRP 1
STR R0, FINAL
LDB R0, SPACE
TRP 3
TRP 3
LDB R0, NewLine
TRP 3

LDR R0, A1
LDR R1, A2
MUL R0, R1
TRP 1
STR R0, INTER
LDB R0, SPACE
TRP 3
TRP 3
LDR R0, INTER
LDR R1, A3
MUL R0, R1
TRP 1
STR R0, INTER
LDB R0, SPACE
TRP 3
TRP 3
LDR R0, INTER
LDR R1, A4
MUL R0, R1
TRP 1
STR R0, INTER
LDB R0, SPACE
TRP 3
TRP 3
LDR R0, INTER
LDR R1, A5
MUL R0, R1
TRP 1
STR R0, INTER
LDB R0, SPACE
TRP 3
TRP 3
LDR R0, INTER
LDR R1, A6
MUL R0, R1
TRP 1
STR R0, INTER
LDB R0, SPACE
TRP 3
TRP 3
LDB R0, NewLine
TRP 3

LDR R0, FINAL
LDR R1, C500
DIV R0, R1
TRP 1
LDB R0, SPACE
TRP 3
TRP 3
LDR R0, FINAL
LDR R1, C2
DIV R0, R1
TRP 1
LDB R0, SPACE
TRP 3
TRP 3
LDR R0, FINAL
LDR R1, C5
DIV R0, R1
TRP 1
LDB R0, SPACE
TRP 3
TRP 3
LDR R0, FINAL
LDR R1, C10
DIV R0, R1
TRP 1
LDB R0, SPACE
TRP 3
TRP 3
LDB R0, NewLine
TRP 3

LDR R0, INTER
LDR R1, C500
SUB R0, R1
TRP 1
LDB R0, SPACE
TRP 3
TRP 3
LDR R0, INTER
LDR R1, C2
SUB R0, R1
TRP 1
LDB R0, SPACE
TRP 3
TRP 3
LDR R0, INTER
LDR R1, C5
SUB R0, R1
TRP 1
LDB R0, SPACE
TRP 3
TRP 3
LDR R0, INTER
LDR R1, C10
SUB R0, R1
TRP 1
LDB R0, SPACE
TRP 3
TRP 3
LDB R0, NewLine
TRP 3

TRP 0