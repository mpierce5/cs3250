#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include "Assembler.h"
using namespace std;

//an int is 2 bytes, 16 bits
int main ( int argc, char *argv[] )
{
	ifstream input_data;
	if(argc != 2)
	{
		cout << "Error, No file passed\n";
		return 0;
	}
	else
	{
		//ifstream in;
		//in.open(argv[1]);
		//in.open("test.txt");
		Assembler assemble;
		assemble.assemble(argv[1]);
		//assemble.assemble("p3.asm");
//		assemble.runVM();
		/*string a,b,c,d,e,f = "";
		string temp = "";
		getline(in,temp);
		istringstream instr(temp);
		instr >> a >> b >> c;
		cout << a << b << c;*/

		//while (in >> a)
		//	cout << a << " ";
		//system("PAUSE");
		//pass source file to assember
		//first pass creates a table storing addresses for all labels
		//first check to see if first word on line is an instruction
		//if it is not an instruction
		return 0;
	}
}