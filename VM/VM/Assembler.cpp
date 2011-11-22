#include "Assembler.h"



Assembler::Assembler(void)
{
	instructions.resize(19);
	instructions[0] = "DIV";
	instructions[1] = "MUL";
	instructions[2] = "LDR";
	instructions[3] = "TRP";
	instructions[4] = "STR";
	instructions[5] = "ADD";
	instructions[6] = "SUB";
	instructions[7] = "LDB";
	instructions[8] = "STB";
	instructions[9] = "JMP";
	instructions[10] = "JMR";
	instructions[11] = "BNZ";
	instructions[12] = "BGT";
	instructions[13] = "BLT";
	instructions[14] = "BRZ";
	instructions[15] = "MOV";
	instructions[16] = "LDA";
	instructions[17] = "CMP";
	instructions[18] = "ADI";

	directives.resize(2);
	directives[0] = ".INT";
	directives[1] = ".BYT";
	
	for(int i = 0; i < 9; i++)
	{
		Registers[i] = 0;
	}
	startingIndex = 0;

}


Assembler::~Assembler(void)
{
}

bool Assembler::assemble(string fileName)
{
	//memory cats;
	//cats.byte1 = 'c';
	//cats.byte2 = 'a';
	//cats.byte3 = 't';
	//cats.byte4 = 's';
	//cout << "cats int value = " << cats.int2 << "\n";

	//cats.byte1 = 't';
	//cats.byte2 = 'a';
	//cats.byte3 = 'c';
	//cats.byte4 = 's';
	//cout << "tacs int value = " << cats.int2 << "\n";

	ifstream in;
	//in.open(argv[1]);
	
	//get the first line of code
	int noMatch = -2;
	string temp = "";
	bool firstPass = true;
	bool stIndSet = false;
	int count = -1;
	int charCount = -4;
	bool addedDirect = false;

	//first pass gets all labels and assigns them an address
	//second pass replaces labels with addresses and creates byte code
	for(int x = 0; x <= 1; x++)
	{
		in.open(fileName);
		while(getline(in,temp))
		{
			
			int type = -1;
			istringstream instr(temp);
			string first ="";
			string second = "";
			int sec;
			instr >> first;
			if(first != "")
			count++;
			charCount++;
			//instr >> second;
			if(first == "" || temp.substr(0,2) == "//")
				charCount--;

			if(firstPass == false && first == ".BYT")
			{
					int value;
					instr >> value;
					memory temp;
					temp.byte1 = value;
					//cout << "index " << charCount << " = " << first << "type " << second << " value " << temp.byte1 << "\n";
					charByteCode[charCount] = temp.byte1;
			}
			else if (firstPass == false && first == ".INT")
			{
				//allocate 4 bytes of memory for an int
				int value;
				memory temp;
				instr >> value;
				temp.int2 = value;		
				//cout << "index " << charCount << " = " << first << "type " << second << " value " << temp.int2 << "\n";
				charByteCode[charCount] = temp.byte1;
				charByteCode[++charCount] = temp.byte2;
				charByteCode[++charCount] = temp.byte3;
				charByteCode[++charCount] = temp.byte4;
			}

			else if(firstPass == false && labelMatch(first))
			{
				//check to see if label is a start point for an instruction or a directive
							
				instr >> second;
				type = instructionMatch(second);
				if(second == ".INT")
					{
						//allocate 4 bytes of memory for an int
						int value;
						memory temp;
						instr >> value;
						temp.int2 = value;
						
						//if(second == ".Int")
						//byteCode[aTable[first]] = temp;

						//cout << "index " << aCharTable[first] << " = " << first << "type " << second << " value " << temp.int2 << "\n";
						charByteCode[charCount] = temp.byte1;
						charByteCode[++charCount] = temp.byte2;
						charByteCode[++charCount] = temp.byte3;
						charByteCode[++charCount] = temp.byte4;
					}
					//allocate first byte as byte value
					else if(second == ".BYT")
					{
						int value;
						instr >> value;
						memory byteToStore;
						byteToStore.int2 = value;
						//if(second == ".BYT")
						//byteCode[aTable[first]] = temp;
						//memory test2 = byteCode[count];
						//cout << "index " << aCharTable[first] << " = " << first << "type " << second << " value " << byteToStore.byte1 << "\n";

						charByteCode[charCount] = byteToStore.int2;
					}
					//if its a label and its not a directive its a label to jump to
					else
					{
						first = second;
					}
			}
	
			//check iF the first word is an instruction
			if(instructionMatch(first) != -1)
			{
				if(firstPass == true)
				{
						charCount = charCount + 3;
				}
				//if its the second pass
				if(firstPass == false)
				{
					if(stIndSet == false)
					{
						startingIndex = count;
						stIndSet = true;
						startingCharIndex = charCount;
					}

					if(first == "ADD")
					{
						memory myInstr;
						myInstr.OpCode = 0;
						char junk;
						string temp;
						
						char dstReg;
						char srcReg;
						instr.get(junk); //space
						instr.get(junk); //R
						instr.get(dstReg); //register number
						instr.get(junk); //comma
						instr.get(junk); //space
						instr.get(junk); //R
						instr.get(srcReg); //register number
						
						myInstr.DestReg = atoi(&dstReg);
						myInstr.SrcReg = atoi(&srcReg);
						byteCode[count] = myInstr;
						//cout <<"index" << count << "added add instruction op code: " << myInstr.OpCode << ", dst reg: " << myInstr.DestReg << "src Reg :" << myInstr.SrcReg << "\n";


						charByteCode[charCount] = myInstr.byte1;
						charByteCode[++charCount] = myInstr.byte2;
						charByteCode[++charCount] = myInstr.byte3;
						charByteCode[++charCount] = myInstr.byte4;
					}
					else if(first == "SUB")
					{
						memory myInstr;
						myInstr.OpCode = 1;
						char junk;
						string temp;
						
						char dstReg;
						char srcReg;
						instr.get(junk); //space
						instr.get(junk); //R
						instr.get(dstReg); //register number
						instr.get(junk); //comma
						instr.get(junk); //space
						instr.get(junk); //R
						instr.get(srcReg); //register number
						
						myInstr.DestReg = atoi(&dstReg);
						myInstr.SrcReg = atoi(&srcReg);
						byteCode[count] = myInstr;
						//cout <<"index" << count << "added sub instruction op code: " << myInstr.OpCode << ", dst reg: " << myInstr.DestReg << "src Reg :" << myInstr.SrcReg << "\n";

						charByteCode[charCount] = myInstr.byte1;
						charByteCode[++charCount] = myInstr.byte2;
						charByteCode[++charCount] = myInstr.byte3;
						charByteCode[++charCount] = myInstr.byte4;
					}
					else if(first == "DIV")
					{
						memory myInstr;
						myInstr.OpCode = 3;
						char junk;
						string temp;
						
						char dstReg;
						char srcReg;
						instr.get(junk); //space
						instr.get(junk); //R
						instr.get(dstReg); //register number
						instr.get(junk); //comma
						instr.get(junk); //space
						instr.get(junk); //R
						instr.get(srcReg); //register number
						
						myInstr.DestReg = atoi(&dstReg);
						myInstr.SrcReg = atoi(&srcReg);
						byteCode[count] = myInstr;
						//cout <<"index" << count << "added div instruction op code: " << myInstr.OpCode << ", dst reg: " << myInstr.DestReg << "src Reg :" << myInstr.SrcReg << "\n";

						charByteCode[charCount] = myInstr.byte1;
						charByteCode[++charCount] = myInstr.byte2;
						charByteCode[++charCount] = myInstr.byte3;
						charByteCode[++charCount] = myInstr.byte4;
					}
					else if(first == "MUL")
					{
						memory myInstr;
						myInstr.OpCode = 2;
						char junk;
						string temp;
						
						char dstReg;
						char srcReg;
						instr.get(junk); //space
						instr.get(junk); //R
						instr.get(dstReg); //register number
						instr.get(junk); //comma
						instr.get(junk); //space
						instr.get(junk); //R
						instr.get(srcReg); //register number
						
						myInstr.DestReg = atoi(&dstReg);
						myInstr.SrcReg = atoi(&srcReg);
						byteCode[count] = myInstr;
						//cout <<"index" << count << "added mul instruction op code: " << myInstr.OpCode << ", dst reg: " << myInstr.DestReg << "src Reg :" << myInstr.SrcReg << "\n";

						charByteCode[charCount] = myInstr.byte1;
						charByteCode[++charCount] = myInstr.byte2;
						charByteCode[++charCount] = myInstr.byte3;
						charByteCode[++charCount] = myInstr.byte4;
					}
					//loads destination register with data from memory
					else if(first == "LDR")
					{
						//store the opcode
						memory myInstr;
						myInstr.OpCode = 4;
						//store the relative address of the data (label)
						char junk, dstReg;
						string temp;
						string label;
						instr.get(junk); //space
						instr.get(junk); //R
						instr.get(dstReg); //register number
						instr.get(junk); //comma
						instr >> label;

						if(label[0] == '*')
						{
							myInstr.OpCode = 6;
							label = label.substr(1,label.size());
						}
						
						//cout << dstReg << "\n";
						myInstr.DestReg = atoi(&dstReg);
						//myInstr.label = aTable[label];
						myInstr.label = aCharTable[label];
						byteCode[count] = myInstr;
						//cout <<"index" << count << "added LDA instruction op code: " << myInstr.OpCode << ", dst reg: " << myInstr.DestReg << "label name: " << label << "label Index: " << myInstr.label << "\n";
						
						charByteCode[charCount] = myInstr.byte1;
						charByteCode[++charCount] = myInstr.byte2;
						charByteCode[++charCount] = myInstr.byte3;
						charByteCode[++charCount] = myInstr.byte4;
					}
					//loads 1 byte into reg, op code 11
					//else if(first == "LDB")
					//{
					//	//store the opcode
					//	memory myInstr;
					//	myInstr.OpCode = 11;
					//	//store the relative address of the data (label)
					//	char junk, dstReg;
					//	string temp;
					//	string label;
					//	instr.get(junk); //space
					//	instr.get(junk); //R
					//	instr.get(dstReg); //register number
					//	instr.get(junk); //comma

					//	instr >> label;
					//	myInstr.DestReg = atoi(&dstReg);
					//	//myInstr.label = aTable[label];
					//	myInstr.label = aCharTable[label];
					//	byteCode[count] = myInstr;
					//	//cout <<"index" << count << "added LDA instruction op code: " << myInstr.OpCode << ", dst reg: " << myInstr.DestReg << "label name: " << label << "label Index: " << myInstr.label << "\n";

					//	charByteCode[charCount] = myInstr.byte1;
					//	charByteCode[++charCount] = myInstr.byte2;
					//	charByteCode[++charCount] = myInstr.byte3;
					//	charByteCode[++charCount] = myInstr.byte4;
					//}
					else if(first == "TRP")
					{
						int trapVal;
						//check for trap 0 ends program opcode 9 for quit
						instr >> trapVal;
						
						//write an integer to standard out - opcode 5, reads from R0
						if (trapVal == 1)
						{
							memory myInstr;
							myInstr.OpCode = 5;
							byteCode[count] = myInstr;
							//cout << "TRAP 1 STORED OP CODE: " << myInstr.OpCode << "\n";

							charByteCode[charCount] = myInstr.byte1;
							charByteCode[++charCount] = myInstr.byte2;
							charByteCode[++charCount] = myInstr.byte3;
							charByteCode[++charCount] = myInstr.byte4;
						}
						//write an integer to standard out - opcode 7, reads from R0
						else if (trapVal == 3)
						{
							memory myInstr;
							myInstr.OpCode = 7;
							byteCode[count] = myInstr;
							//cout << "TRAP 3 STORED OP CODE: " << myInstr.OpCode << "\n";

							charByteCode[charCount] = myInstr.byte1;
							charByteCode[++charCount] = myInstr.byte2;
							charByteCode[++charCount] = myInstr.byte3;
							charByteCode[++charCount] = myInstr.byte4;
						}
						else if (trapVal == 0)
						{
							memory myInstr;
							myInstr.OpCode = 9;
							byteCode[count] = myInstr;
							//cout << "END, STORED OP CODE: " << myInstr.OpCode;

							charByteCode[charCount] = myInstr.byte1;
							charByteCode[++charCount] = myInstr.byte2;
							charByteCode[++charCount] = myInstr.byte3;
							charByteCode[++charCount] = myInstr.byte4;
						}
						//reads a char from standard in, opdcode 24
						else if (trapVal == 4)
						{
							memory myInstr;
							myInstr.OpCode = 24;
							byteCode[count] = myInstr;
							//cout << "END, STORED OP CODE: " << myInstr.OpCode;

							charByteCode[charCount] = myInstr.byte1;
							charByteCode[++charCount] = myInstr.byte2;
							charByteCode[++charCount] = myInstr.byte3;
							charByteCode[++charCount] = myInstr.byte4;
						}
					
					}
					//store data into memory from a register
					else if(first == "STR")
					{
						//op Code 10
						//store the opcode
						memory myInstr;
						myInstr.OpCode = 10;
						//store the data 
						char junk, srcReg;
						string temp;
						string label;
						instr.get(junk); //space
						instr.get(junk); //R
						instr.get(srcReg); //register number
						instr.get(junk); //comma
						instr >> label;

						if(label[0] == '*')
						{
							myInstr.OpCode = 8;
							label = label.substr(1,label.size());
						}


						myInstr.SrcRegSTR = atoi(&srcReg);
						//myInstr.label = aTable[label];
						myInstr.label = aCharTable[label];
						//byteCode[count] = myInstr;

						charByteCode[charCount] = myInstr.byte1;
						charByteCode[++charCount] = myInstr.byte2;
						charByteCode[++charCount] = myInstr.byte3;
						charByteCode[++charCount] = myInstr.byte4;

					//	cout <<"index" << count << "added STR instruction op code: " << myInstr.OpCode << ", src reg: " << myInstr.DestReg << "label name: " << label << "label Index: " << myInstr.label << "\n";
					
					}
					//stores the add instruction in the memory vector
					//first byte, instruction, second byte
					
					//else if (first == "END")
					//	{
					//		memory myInstr;
					//		myInstr.OpCode = 9;
					//		byteCode[count] = myInstr;
					//		//cout << "END, STORED OP CODE: " << myInstr.OpCode;
					//	}
					
					//loads 1 byte into reg, op code 11
					else if(first == "LDB")
					{
						//store the opcode
						memory myInstr;
						myInstr.OpCode = 11;
						//store the relative address of the data (label)
						char junk, dstReg;
						string temp;
						string label;
						instr.get(junk); //space
						instr.get(junk); //R
						instr.get(dstReg); //register number
						instr.get(junk); //comma
						instr >> label; //the label where the byte is store

						if(label[0] == '*')
						{
							myInstr.OpCode = 25;
							label = label.substr(1,label.size());
						}
						
						
						myInstr.DestReg = atoi(&dstReg);
						//myInstr.label = aTable[label];
						myInstr.label = aCharTable[label];
						byteCode[count] = myInstr;
						//cout <<"index" << count << "added LDB instruction op code: " << myInstr.OpCode << ", dst reg: " << myInstr.DestReg << "label name: " << label << "label Index: " << myInstr.label << "\n";

						charByteCode[charCount] = myInstr.byte1;
						charByteCode[++charCount] = myInstr.byte2;
						charByteCode[++charCount] = myInstr.byte3;
						charByteCode[++charCount] = myInstr.byte4;
					}
					//store 1 byte into memory from a register, op code 12
					else if(first == "STB")
					{
						//store the opcode
						memory myInstr;
						myInstr.OpCode = 12;
						//store the data 
						char junk, srcReg;
						string temp;
						string label;
						instr.get(junk); //space
						instr.get(junk); //R
						instr.get(srcReg); //register number
						instr.get(junk); //comma
						instr >> label;


						if(label[0] == '*')
						{
							myInstr.OpCode = 23;
							label = label.substr(1,label.size());
						}
						
						myInstr.SrcRegSTR = atoi(&srcReg);
						//myInstr.label = aTable[label];
						myInstr.label = aCharTable[label];
						byteCode[count] = myInstr;


						//cout <<"index" << count << "added STB instruction op code: " << myInstr.OpCode << ", src reg: " << myInstr.DestReg << "label name: " << label << "label Index: " << myInstr.label << "\n";
					
						charByteCode[charCount] = myInstr.byte1;
						charByteCode[++charCount] = myInstr.byte2;
						charByteCode[++charCount] = myInstr.byte3;
						charByteCode[++charCount] = myInstr.byte4;
					}
					//STORE OPCODE, STORE LABEL LOCATION
					else if(first == "JMP")
					{
						//op Code 10
						//store the opcode
						memory myInstr;
						myInstr.OpCode = 13;
						//store the data 
						char junk, srcReg;
						string label;
						instr >> label;
						//myInstr.label = aTable[label];
						myInstr.label = aCharTable[label];
						byteCode[count] = myInstr;


						//cout <<"index" << count << "added JMP instruction op code: " << myInstr.OpCode << "label name: " << label << "label Index: " << myInstr.label << "\n";
					
						charByteCode[charCount] = myInstr.byte1;
						charByteCode[++charCount] = myInstr.byte2;
						charByteCode[++charCount] = myInstr.byte3;
						charByteCode[++charCount] = myInstr.byte4;
					}
					//BRANCH TO ADDRESS IN SOURCE REGISTER, OP CODE 14
					else if(first == "JMR")
					{
						
						//store the opcode
						memory myInstr;
						myInstr.OpCode = 14;
						//store the data 
						char junk, srcReg;
						instr.get(junk); //space
						instr.get(junk); //R
						instr.get(srcReg); //register number
						instr.get(junk); //comma
						//myInstr.label = aTable[label];
						myInstr.SrcRegSTR = atoi(&srcReg);
						//byteCode[count] = myInstr;
						//cout <<"index" << count << "added JMR instruction op code: " << myInstr.OpCode << "Source Register: " << myInstr.SrcRegSTR << "\n";
					
						charByteCode[charCount] = myInstr.byte1;
						charByteCode[++charCount] = myInstr.byte2;
						charByteCode[++charCount] = myInstr.byte3;
						charByteCode[++charCount] = myInstr.byte4;
					}
					//Branch to label if source register is not zero, OP CODE 15
					else if(first == "BNZ")
					{
						
						//store the opcode
						memory myInstr;
						myInstr.OpCode = 15;
						//store the data 
						char junk, srcReg;
						string label;
						instr.get(junk); //space
						instr.get(junk); //R
						instr.get(srcReg); //register number
						instr.get(junk); //comma
						instr >> label; //the label where the byte is stored
						myInstr.label = aCharTable[label];
						myInstr.SrcRegSTR = atoi(&srcReg);
						//byteCode[count] = myInstr;
						//cout <<"index" << count << "added BNZ instruction op code: " << myInstr.OpCode << "Source Register: " << myInstr.SrcRegSTR << "label name: " << label << "label Index: " << myInstr.label << "\n";
					
						charByteCode[charCount] = myInstr.byte1;
						charByteCode[++charCount] = myInstr.byte2;
						charByteCode[++charCount] = myInstr.byte3;
						charByteCode[++charCount] = myInstr.byte4;
					}
					//Branch to label if source register is Greater than zero, OP CODE 16
					else if(first == "BGT")
					{
						
						//store the opcode
						memory myInstr;
						myInstr.OpCode = 16;
						//store the data 
						char junk, srcReg;
						string label;
						instr.get(junk); //space
						instr.get(junk); //R
						instr.get(srcReg); //register number
						instr.get(junk); //comma
						instr >> label; //the label where the byte is stored
						myInstr.label = aCharTable[label];
						myInstr.SrcRegSTR = atoi(&srcReg);
						//byteCode[count] = myInstr;
						//cout <<"index" << count << "added BGT instruction op code: " << myInstr.OpCode << "Source Register: " << myInstr.SrcRegSTR << "label name: " << label << "label Index: " << myInstr.label << "\n";
					
						charByteCode[charCount] = myInstr.byte1;
						charByteCode[++charCount] = myInstr.byte2;
						charByteCode[++charCount] = myInstr.byte3;
						charByteCode[++charCount] = myInstr.byte4;
					}
					//Branch to label if source register is less than zero, OP CODE 17
					else if(first == "BLT")
					{
						
						//store the opcode
						memory myInstr;
						myInstr.OpCode = 17;
						//store the data 
						char junk, srcReg;
						string label;
						instr.get(junk); //space
						instr.get(junk); //R
						instr.get(srcReg); //register number
						instr.get(junk); //comma
						instr >> label; //the label where the byte is stored
						myInstr.label = aCharTable[label];
						myInstr.SrcRegSTR = atoi(&srcReg);
						//byteCode[count] = myInstr;
						//cout <<"index" << count << "added BLT instruction op code: " << myInstr.OpCode << "Source Register: " << myInstr.SrcRegSTR << "label name: " << label << "label Index: " << myInstr.label << "\n";
					
						charByteCode[charCount] = myInstr.byte1;
						charByteCode[++charCount] = myInstr.byte2;
						charByteCode[++charCount] = myInstr.byte3;
						charByteCode[++charCount] = myInstr.byte4;
					}
					//Branch to label if source register is zero, OP CODE 18
					else if(first == "BRZ")
					{
						
						//store the opcode
						memory myInstr;
						myInstr.OpCode = 18;
						//store the data 
						char junk, srcReg;
						string label;
						instr.get(junk); //space
						instr.get(junk); //R
						instr.get(srcReg); //register number
						instr.get(junk); //comma
						instr >> label; //the label where the byte is stored
						myInstr.label = aCharTable[label];
						myInstr.SrcRegSTR = atoi(&srcReg);
						//byteCode[count] = myInstr;
						//cout <<"index" << count << "added BRZ instruction op code: " << myInstr.OpCode << "Source Register: " << myInstr.SrcRegSTR << "label name: " << label << "label Index: " << myInstr.label << "\n";
					
						charByteCode[charCount] = myInstr.byte1;
						charByteCode[++charCount] = myInstr.byte2;
						charByteCode[++charCount] = myInstr.byte3;
						charByteCode[++charCount] = myInstr.byte4;
					}
					//moves data from one register to another, op code 19
					else if(first == "MOV")
					{
						//store the opcode
						memory myInstr;
						myInstr.OpCode = 19;
						//store the relative address of the data (label)
						char junk, dstReg, srcReg;
						string temp;
						string label;
						instr.get(junk); //space
						instr.get(junk); //R
						instr.get(dstReg); //register number
						instr.get(junk); //comma
						
						instr.get(junk); //space
						instr.get(junk); //R
						instr.get(srcReg); //register number

						myInstr.DestReg = atoi(&dstReg);
						myInstr.SrcReg = atoi(&srcReg);
						byteCode[count] = myInstr;
						//cout <<"index" << count << "added MOV instruction op code: " << myInstr.OpCode << ", dst reg: " << myInstr.DestReg << "Src Reg: " << srcReg << "\n";
						
						charByteCode[charCount] = myInstr.byte1;
						charByteCode[++charCount] = myInstr.byte2;
						charByteCode[++charCount] = myInstr.byte3;
						charByteCode[++charCount] = myInstr.byte4;
					}
					//Loads the destination register with address in label, op Code 20
					else if(first == "LDA")
					{
						//store the opcode
						memory myInstr;
						myInstr.OpCode = 20;
						//store the relative address of the data (label)
						char junk, dstReg;
						string temp;
						string label;
						instr.get(junk); //space
						instr.get(junk); //R
						instr.get(dstReg); //register number
						instr.get(junk); //comma
						
						instr >> label; //space
						int address = aCharTable[label];

						myInstr.DestReg = atoi(&dstReg);
						myInstr.label = address;

						byteCode[count] = myInstr;
						//cout <<"index" << count << "added LDA instruction op code: " << myInstr.OpCode << ", dst reg: " << myInstr.DestReg << "label Address: " << address << "\n";
						
						charByteCode[charCount] = myInstr.byte1;
						charByteCode[++charCount] = myInstr.byte2;
						charByteCode[++charCount] = myInstr.byte3;
						charByteCode[++charCount] = myInstr.byte4;
					}
					//compare two regisers, set dest to 0 if equal to source, set dest reg > 0 if dest is > source, set dest < 0 if dest < src, op Code 21
					else if(first == "CMP")
					{
						//store the opcode
						memory myInstr;
						myInstr.OpCode = 21;
						//store the relative address of the data (label)
						char junk, dstReg, srcReg;
						string temp;
						string label;
						instr.get(junk); //space
						instr.get(junk); //R
						instr.get(dstReg); //register number
						instr.get(junk); //comma
						
						instr.get(junk); //space
						instr.get(junk); //R
						instr.get(srcReg); //register number

						myInstr.DestReg = atoi(&dstReg);
						myInstr.SrcReg = atoi(&srcReg);
						byteCode[count] = myInstr;
						//cout <<"index" << count << "added CMP instruction op code: " << myInstr.OpCode << ", dst reg: " << myInstr.DestReg << "Src Reg: " << srcReg << "\n";
						
						charByteCode[charCount] = myInstr.byte1;
						charByteCode[++charCount] = myInstr.byte2;
						charByteCode[++charCount] = myInstr.byte3;
						charByteCode[++charCount] = myInstr.byte4;
					}
					//ADD IMMEDIATE VALUE TO DEST REGISTER, OP CODE 22
					else if(first == "ADI")
					{
						memory myInstr;
						myInstr.OpCode = 22;
						char junk;
						string temp;
						
						char dstReg;
						char srcReg;
						instr.get(junk); //space
						instr.get(junk); //R
						instr.get(dstReg); //register number
						instr.get(junk); //comma
						instr.get(junk); //space
						int immVal = 0;
						instr >> immVal;
						myInstr.SrcReg = immVal;
						myInstr.DestReg = atoi(&dstReg);
						//cout <<"index" << charCount << "added ADI instruction op code: " << myInstr.OpCode << ", dst reg: " << myInstr.DestReg << "value :" << myInstr.label << "\n";


						charByteCode[charCount] = myInstr.byte1;
						charByteCode[++charCount] = myInstr.byte2;
						charByteCode[++charCount] = myInstr.byte3;
						charByteCode[++charCount] = myInstr.byte4;
					}

				}
			}
			//check to see if the first instruction is already stored in the assembly table
			else if(labelMatch(first) && firstPass == true)
			{
				charCount--;
			//	cout << "error " << first << " already defined\n";
			}
			
			//if it is .int or .byt without a label it is in an array, allocate storage in table
			else if(first == ".INT" && firstPass == true)
			{
				if(charCount == -3)
					charCount = charCount+3;
					charCount = charCount+3;
			}
			else if(first == ".BYT" && firstPass == true)
			{
				if(charCount == -3)
					charCount = charCount+3;
			}
			
			
			//if it is not in either it is a label, store in assembly table with address
			else if(first != "" && firstPass == true &&  temp.substr(0,2) != "//")
			{
				aTable[first] = count;
				instr >> second;
				if(second == ".INT")
				{
					if(charCount == -3)
						charCount = charCount+3;
					aCharTable[first] = charCount;
					charCount = charCount+3;
				}	
				else if(second == ".BYT")
				{
					if(charCount == -3)
						charCount = charCount+3;
					aCharTable[first] = charCount;
				}
				else
				{
					if(charCount == -3)
						charCount = charCount+3;
					aCharTable[first] = charCount;
					if (instr >> second != ".BYT")
					charCount = charCount + 3;
				}
	
					//if it is not a directive it is an instruction
					//else
					//{
					//	
					//	//aTable[first] = new char[8];
					//	cout << first << " is an instruction label" << "\n";
					//}
					//allocate number of chars based on the type, Instruction 32 bits, 8 bytes
						
			}
		
		}//end of while loop
		//end of first pass
		if (firstPass == true)
			byteCode.resize(count+1);
			charByteCode.resize(charCount*2);
		firstPass = false;
		count = -1;
		charCount = -1;
		in.close();
	}//end of for loop
	runVM();
	return true;
}

int Assembler::instructionMatch(string tInst)
{
	if(tInst == "")
	{
		//cout << "Error Testing for blank instruction" << "\n";
		return -1;
	}

	for(int i = 0; i < instructions.size(); i++)
	{
		if(tInst == instructions[i])
			return i;
	}
	return -1;
}
bool Assembler::labelMatch(string tLabel)
{
	
	map<string, int>::iterator p = aCharTable.find(tLabel);
	if(p == aCharTable.end())
		return false;
	else
		return true;
}

//the VM will read each parse and run each instruction
void Assembler::runVM2()
{
	//loop ends when END is found, when this occurs i will be set to a value less than 0, exiting loop otherwise
	//it runs until it breaks
	for(int i = startingIndex; i >= 0; i ++)
	{
		//read instruction 
		memory execInstr = byteCode[i];
		////check if it is a directive
		//if(execInstr.directive == 999 || execInstr.charDirective == 999)
		//{
		//	//do nothing
		//	//cout << "instr " << i << "is a directive\n";
		//}
		//check for addition, add source to destination, store in destination register
		if(execInstr.OpCode == 0)
		{
			Registers[execInstr.DestReg] = Registers[execInstr.DestReg] + Registers[execInstr.SrcReg];
		}
		//check for subtraction, sub source from dest, store in dest reg
		else if(execInstr.OpCode == 1)
		{
			Registers[execInstr.DestReg] = Registers[execInstr.DestReg] - Registers[execInstr.SrcReg];
		}
		//check for multiplaction, mult source by dest, store in dest reg
		else if(execInstr.OpCode == 2)
		{
			Registers[execInstr.DestReg] = Registers[execInstr.DestReg] * Registers[execInstr.SrcReg];
		}
		//check for division, divide dest reg by source, store in dest reg
		else if(execInstr.OpCode == 3)
		{
			Registers[execInstr.DestReg] = Registers[execInstr.DestReg] / Registers[execInstr.SrcReg];
		}
		//check for LDR, load value of data in label label into src reg
		//an int is 2 bytes, loads 2 bytes and puts in specified register
		else if(execInstr.OpCode == 4)
		{
			int destReg = execInstr.DestReg;
			int label = execInstr.label;
			int value = byteCode[label].int2;
			//cout << "executing instruction: Dest reg = " << execInstr.DestReg << " label: " << execInstr.label << "\n";
			Registers[destReg] = value;
		}
		//check for trp 1, write integer to standard out
		else if(execInstr.OpCode == 5)
		{
			cout << dec << Registers[0];
		}
		//chep for trp 3, print a char to standard out
		else if(execInstr.OpCode == 7)
		{
			memory output;
			output.byte1 = Registers[0];
			char x = output.byte1;
			cout << x;
		}
		//check for TRP 0, opcode 9
		else if(execInstr.OpCode == 9)
		{
			i=-2;
		}
		//check for STR, opcode 10
		else if(execInstr.OpCode == 10)
		{
			memory storage;
			//store the value in the specified register into label in memory
			storage.int2 = Registers[execInstr.SrcRegSTR];
			byteCode[execInstr.label] = storage;
		}
		//check for LDB, opcode 11
		else if(execInstr.OpCode == 11)
		{

			int destReg = execInstr.DestReg;
			int label = execInstr.label;
			int value = byteCode[label].byte1;
			//cout << "executing instruction: Dest reg = " << execInstr.DestReg << " label: " << execInstr.label << "\n";
			Registers[destReg] = value;

		}
		//check for STB, opcode 12
		else if(execInstr.OpCode == 12)
		{
			memory storage;
			//store the value in the specified register into label in memory
			storage.byte1 = Registers[execInstr.SrcRegSTR];
			byteCode[execInstr.label] = storage;
		}

	}
}

//the VM will read each parse and run each instruction
void Assembler::runVM()
{
	//loop ends when END is found, when this occurs i will be set to a value less than 0, exiting loop otherwise
	//it runs until it breaks
	for(int i = startingCharIndex; i >= 0; i ++)
	{
		//read instruction 
		memory execInstr;
		execInstr.byte1 = charByteCode[i];
		execInstr.byte2 = charByteCode[++i];
		execInstr.byte3 = charByteCode[++i];
		execInstr.byte4 = charByteCode[++i];

		//check for addition, add source to destination, store in destination register
		if(execInstr.OpCode == 0)
		{
			Registers[execInstr.DestReg] = Registers[execInstr.DestReg] + Registers[execInstr.SrcReg];
		}
		//check for subtraction, sub source from dest, store in dest reg
		else if(execInstr.OpCode == 1)
		{
			Registers[execInstr.DestReg] = Registers[execInstr.DestReg] - Registers[execInstr.SrcReg];
		}
		//check for multiplaction, mult source by dest, store in dest reg
		else if(execInstr.OpCode == 2)
		{
			Registers[execInstr.DestReg] = Registers[execInstr.DestReg] * Registers[execInstr.SrcReg];
		}
		//check for division, divide dest reg by source, store in dest reg
		else if(execInstr.OpCode == 3)
		{
			Registers[execInstr.DestReg] = Registers[execInstr.DestReg] / Registers[execInstr.SrcReg];
		}
		//check for LDR, load value of data in label into src reg
		//an int is 4 bytes, loads 4 bytes and puts in specified register
		else if(execInstr.OpCode == 4)
		{
			int destReg = execInstr.DestReg;
			int label = execInstr.label;
			//aCharTable[label];
			memory x;
			x.byte1 = charByteCode[label];
			x.byte2 = charByteCode[label+1];
			x.byte3 = charByteCode[label+2];
			x.byte4 = charByteCode[label+3];
			int value = x.int2;
			//cout << "executing instruction: Dest reg = " << execInstr.DestReg << " label: " << execInstr.label << "\n";
			Registers[destReg] = value;
		}
		//check for trp 1, write integer to standard out
		else if(execInstr.OpCode == 5)
		{
			cout << dec << Registers[0];
		}
		//check for trp 3, print a char to standard out
		else if(execInstr.OpCode == 7)
		{
			memory output;
			output.byte1 = Registers[0];
			char x = output.byte1;
			cout << x;
		}
		//check for TRP 0, opcode 9
		else if(execInstr.OpCode == 9)
		{
			i=-2;
		}
		//check for TRP 4, opcode 24
		else if(execInstr.OpCode == 24)
		{
			memory output;
			Registers[0] = getchar();
			//cout << Registers[0] << " stored in reg 1\n";
		}
		//check for STR, opcode 10
		else if(execInstr.OpCode == 10)
		{
			memory storage;
			//store the value in the specified register into label in memory
			storage.int2 = Registers[execInstr.SrcRegSTR];

			int loc = execInstr.label;
			charByteCode[loc] = storage.byte1;
			charByteCode[++loc] = storage.byte2;
			charByteCode[++loc] = storage.byte3;
			charByteCode[++loc] = storage.byte4;

		//go to value stored at this int value


			//aCharTable[execInstr.label] = storage;
		}
		//check for LDB, opcode 11
		else if(execInstr.OpCode == 11)
		{

			int destReg = execInstr.DestReg;
			int label = execInstr.label;
			int value = charByteCode[label];
			//cout << "executing instruction: Dest reg = " << execInstr.DestReg << " label: " << execInstr.label << "\n";
			Registers[destReg] = value;

		}
		//check for STB, opcode 12
		else if(execInstr.OpCode == 12)
		{
			memory storage;
			//store the value in the specified register into label in memory
			storage.byte1 = Registers[execInstr.SrcRegSTR];
			int loc = execInstr.label;
			charByteCode[loc] = storage.byte1;
		}
		//check for JMP, opcode 13
		else if(execInstr.OpCode == 13)
		{
			//change PC (i) to location in jump
			i = execInstr.label - 1;
		}
		//check for JMR, opcode 14, branches to the address in the source register
		else if(execInstr.OpCode == 14)
		{
			//get register with address
			int x = execInstr.DestReg;
			//store change pc to value in x
			i = Registers[x] - 1;
		}
		//check for BNZ, branch to label if source register is not zero, op code 15
		else if(execInstr.OpCode == 15)
		{
			if(Registers[execInstr.SrcRegSTR] != 0)
			{
				i = execInstr.label - 1;
			}
		}
		//check for BGT, branch to label if source register is Greater than zero, op Code 16
		else if(execInstr.OpCode == 16)
		{
			if(Registers[execInstr.SrcRegSTR] > 0)
			{
				i = execInstr.label - 1;
			}
		}
		//check for BLT, branch to label if source register is Less than zero, op Code 17
		else if(execInstr.OpCode == 17)
		{
			if(Registers[execInstr.SrcRegSTR] < 0)
			{
				i = execInstr.label - 1;
			}
		}
		//check for BRZ, branch to label if source register is zero, op code 18
		else if(execInstr.OpCode == 18)
		{
			if(Registers[execInstr.SrcRegSTR] == 0)
			{
				i = execInstr.label - 1;
			}
		}
		//check for MOV, moves data from one register to another, op code 19
		else if(execInstr.OpCode == 19)
		{
			Registers[execInstr.DestReg] = Registers[execInstr.SrcReg];
		}		
		//check for LDA, opcode 20, loads address of label into register
		else if(execInstr.OpCode == 20)
		{
			int destReg = execInstr.DestReg;
			int label = execInstr.label;
			//cout << "executing instruction: Dest reg = " << execInstr.DestReg << " label: " << execInstr.label << "\n";
			Registers[destReg] = label;
		}
		//check for CMP, set dest to 0 if equal to source, set dest reg > 0 if dest is > source, set dest < 0 if dest < src, op Code 21
		else if(execInstr.OpCode == 21)
		{
			if(Registers[execInstr.DestReg] == Registers[execInstr.SrcReg])
				Registers[execInstr.DestReg] = 0;
			else if(Registers[execInstr.DestReg] > Registers[execInstr.SrcReg])
				Registers[execInstr.DestReg] = 1;
			else if(Registers[execInstr.DestReg] < Registers[execInstr.SrcReg])
				Registers[execInstr.DestReg] = -1;
		}
		//check for ADI, adds immediate value to destination register, opcode 22
		else if(execInstr.OpCode == 22)
		{
			Registers[execInstr.DestReg] = Registers[execInstr.DestReg] + execInstr.SrcReg;
		}
		//check for LDR indirect, opcode 6
		else if(execInstr.OpCode == 6)
		{
			int destReg = execInstr.DestReg;
			//get the address to look for value inside of the label
			int address = execInstr.label;
			memory x;
			x.byte1 = charByteCode[address];
			x.byte2 = charByteCode[address+1];
			x.byte3 = charByteCode[address+2];
			x.byte4 = charByteCode[address+3];
			//go to value stored at this int value
			int label = x.int2;
			x.byte1 = charByteCode[label];
			x.byte2 = charByteCode[label+1];
			x.byte3 = charByteCode[label+2];
			x.byte4 = charByteCode[label+3];
			int value = x.int2;
			Registers[execInstr.DestReg] = value;
		}
		//CHECK FOR STB INDIRECT, opcode 23
		else if(execInstr.OpCode == 23)
		{
			memory x;
			int address = execInstr.label;
			//store the value in the specified register into reg in memory
			x.byte1 = charByteCode[address];
			x.byte2 = charByteCode[address+1];
			x.byte3 = charByteCode[address+2];
			x.byte4 = charByteCode[address+3];
			//go to value stored at this int value
			int label = x.int2;
			x.byte1 = Registers[execInstr.SrcRegSTR]; //value
			//go to this address and 
			charByteCode[label] = x.byte1;
		}
		//CHECK FOR LDB INDIRECT, opcode 25
		else if(execInstr.OpCode == 25)
		{
			memory x;
			int address = execInstr.label;
			//store the value in the specified register into reg in memory
			x.byte1 = charByteCode[address];
			x.byte2 = charByteCode[address+1];
			x.byte3 = charByteCode[address+2];
			x.byte4 = charByteCode[address+3];
			//go to value stored at this int value
			int destReg = execInstr.DestReg;
			int label = x.int2;
			int value = charByteCode[label];
			//cout << "executing instruction: Dest reg = " << execInstr.DestReg << " label: " << execInstr.label << "\n";
			Registers[destReg] = value;
		}
	}
} 