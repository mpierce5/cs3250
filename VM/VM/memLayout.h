#pragma once
class memLayout
{
public:
	memLayout(void);
	~memLayout(void);
	
	union memory
	{
	int instruction;
	
	//ADD
	//BITS 1-8 = OP CODE
	//BITS 9-16 REG DESTINATION
	//BITS 17-24 SOURCE REG
	struct
	{
		unsigned OpCode: 8;
		unsigned RD: 8;
		unsigned SR: 8;
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
		unsigned int2: 32;
	};

	struct
	{
		unsigned bit32: 1;
		unsigned bit31: 1;
		unsigned bit30: 1;
		unsigned bit29: 1;
		unsigned bit28: 1;
		unsigned bit27: 1;
		unsigned bit26: 1;
		unsigned bit25: 1;
		unsigned bit24: 1;
		unsigned bit23: 1;
		unsigned bit22: 1;
		unsigned bit21: 1;
		unsigned bit20: 1;
		unsigned bit19: 1;
		unsigned bit18: 1;
		unsigned bit17: 1;
		unsigned bit16: 1;
		unsigned bit15: 1;
		unsigned bit14: 1;
		unsigned bit13: 1;
		unsigned bit12: 1;
		unsigned bit11: 1;
		unsigned bit10: 1;
		unsigned bit9: 1;
		unsigned bit8: 1;
		unsigned bit7: 1;
		unsigned bit6: 1;
		unsigned bit5: 1;
		unsigned bit4: 1;
		unsigned bit3: 1;
		unsigned bit2: 1;
		unsigned bit1: 1;
	};
};

	void InstAdd(char* instructions);
};

