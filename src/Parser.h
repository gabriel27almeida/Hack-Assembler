#ifndef __PARSER__
#define __PARSER__

#include <string>
#include <fstream>
#include "SymbolTable.h"

/*
This class is responsible for dealing with the instructions file.
Its methods are:

- Advance. If there are more instructions, it selects 
the next instruction and returns 1. Else, it returns 0.

- FirstPassage. Handle label declaration statements "(LABEL)"

- Reset. Goes to beginning of the file

- GetInstruction. Getter for selected instruction

- GetPC. Getter for Program Counter (number of selected instruction)
*/

class Parser {
public:
	Parser(std::string fileName, SymbolTable*);
	Parser()=default;
	~Parser();

	// Flow control

	bool Advance(bool firstPassage=false); //if FirstPassage, doesn't ignore label declarations 
	void FirstPassage();
	void Reset();

	//Getters

	std::string GetInstruction();
	int GetPC();

private:
	std::string fileName;
	std::ifstream File;
	std::string CurrentInstruction;
	int PC; //Program Counter

	SymbolTable* table;
};

#endif