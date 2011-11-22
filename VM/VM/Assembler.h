#pragma once
#include <string>
#include <fstream>
#include <map>
#include <sstream>
#include <vector>
#include <iostream>
union memory
{
	int instruction;
	char byte[4];
	struct
	{
		unsigned OpCode: 8;
		unsigned DestReg: 4;
		unsigned SrcReg: 20;
	};

	struct
	{
		unsigned OpCode: 8;
		unsigned DestReg: 4;
		unsigned label: 20;
	};

	struct
	{
		unsigned OpCode: 8;
		unsigned SrcRegSTR: 4;
		unsigned label: 20;
	};

	struct
	{
		unsigned byte4: 8;
		unsigned byte3: 8;
		unsigned byte2: 8;
		unsigned byte1: 8;
	};
	struct
	{
		int int2: 32;
	};

};
using namespace std;
class Assembler
{
public:
	Assembler(void);
	~Assembler(void);
	bool assemble(string in);
	int instructionMatch(string tInst);
	bool labelMatch(string tLabel);
	void runVM();
	void runVM2();
	private:
	int SIZE;
	vector<string> instructions;
	vector<string> directives;
	//takes a name - 
	map<string,int> aTable;
	map<string,int> aCharTable;
	vector<memory> byteCode;
	int Registers[10];
	int startingIndex;
	int startingCharIndex;
	vector<char> charByteCode;
	
};

