#include "Memory.h"
union memory
{
	int instruction;
	char byte[4];
	//ADD
	//BITS 1-8 = OP CODE
	//BITS 9-16 REG DESTINATION
	//BITS 17-24 SOURCE REG
	struct
	{
		unsigned OpCode: 4;
		unsigned DestReg: 3;
		unsigned SrcReg: 25;
	};

	struct
	{
		unsigned OpCode: 4;
		unsigned DestReg: 3;
		unsigned label: 25;
	};

	struct
	{
		unsigned OpCode: 4;
		unsigned SrcRegSTR: 3;
		unsigned label: 25;
	};

	struct
	{
		unsigned charDirective: 16;
		unsigned byte2: 8;
		unsigned byte1: 8;
	};
	struct
	{
		unsigned directive: 16;
		unsigned int2: 16;
	};

};

Memory::Memory(void)
{
}


Memory::~Memory(void)
{
}
