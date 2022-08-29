#ifndef __INSTRUCTION__
#define __INSTRUCTION__

#include <string>
#include <map>
#include <vector>
#include "SymbolTable.h"

/*
This class is responsible for interpreting and decoding an instruction.

Its public methods are:

- isAinstruction
- decodeA
- decodeC

Its private auxiliary methods are:

- toBinary. Decimal to binary representation converter

- isSymbolic. Determines if string is not numeric
- GetAddress. Gets address of numeric A instruction

- DecodeDest. Decodes destination segment of C instruction
- DecodeJump. Decodes jump segment of C instruction
- DecodeComp. Decodes computation segment of C instruction
*/

class Instruction {
public:
	Instruction(std::string, SymbolTable*);
	~Instruction()=default;

	bool isAinstruction();	
	void decodeA(bool*);
	void decodeC(bool*);

private:
	std::string Content;
	SymbolTable* table;

	static std::vector<std::string> destMap, jumpMap;
	static std::map<std::string, int> compMap;

	//decimal to binary converter
	static void toBinary(int num, int width, bool* dest);

	// helper methods for A instructions
	bool isSymbolic();
	int GetAddress();

	// helper methods for C instructions
	static void decodeDest(std::string, bool* code);
	static void decodeJump(std::string, bool* code);
	static void decodeComp(std::string, bool* code);
};

#endif