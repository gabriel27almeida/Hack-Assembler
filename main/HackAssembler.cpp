#include <string>
#include "Parser.h"
#include "Instruction.h"
#include "SymbolTable.h"

int main(int argc, char** argv) {
	std::string fileName = argv[1];

	SymbolTable table;
	Parser p(fileName, &table);

	p.FirstPassage();
	p.Reset();

	std::ofstream binFile(std::string(fileName,0, fileName.size()-3) + "hack");

	while(p.Advance()){
		Instruction i(p.GetInstruction(), &table);
		bool code[16];

		if (i.isAinstruction()) i.decodeA(code);
		else i.decodeC(code);

		for(auto u: code) binFile << u;
		binFile << "\n";
	}

	binFile.close();
}