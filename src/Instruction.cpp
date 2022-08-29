#include "Instruction.h"

// Declaration of static members

std::vector<std::string> Instruction::destMap={"","M","D","MD","A","AM","AD","AMD"};
std::vector<std::string> Instruction::jumpMap={"","JGT","JEQ","JGE","JLT","JNE","JLE","JMP"};
std::map<std::string, int> Instruction::compMap={
	{"0", 42},
	{"1", 63},
	{"-1",58},
	{"D", 12},
	{"A", 48},
	{"!D",13},
	{"!A",49},
	{"-D",15},
	{"-A",51},
	{"D+1",31},
	{"A+1",55},
	{"D-1",14},
	{"A-1",50},
	{"D+A",2},
	{"D-A",19},
	{"A-D",7},
	{"D&A",0},
	{"D|A",21},
	{"M",112},
	{"!M",113},
	{"-M", 115},
	{"M+1",119},
	{"M-1",114},
	{"D+M",66},
	{"D-M",83},
	{"M-D",71},
	{"D&M",64},
	{"D|M",85}
};


////////////////////////
////// CONSTRUCTOR

Instruction::Instruction(std::string cont, SymbolTable* t){
	Content = cont;
	table = t;
}

////////////////////////
////// IS A INSTRUCTION

bool Instruction::isAinstruction(){
	return Content[0]=='@';
}

////////////////////////
////// DECODE A

void Instruction::decodeA(bool* code){
	int addr;
	if (this->isSymbolic()){
		addr = (*table)[std::string(Content, 1, Content.size()-1)];
	}
	else addr = this->GetAddress();

	toBinary(addr, 16, code);
}

////////////////////////
////// GET ADDRESS

int Instruction::GetAddress(){
	int addr=0;
	for(int i=1; i<Content.size(); i++){
		addr*=10;
		addr += (int) Content[i] - '0';
	}
	return addr;
}

////////////////////////
////// IS SYMBOLIC

bool Instruction::isSymbolic(){
	for(auto it=Content.begin() + 1; it!=Content.end(); it++){
		if(! std::isdigit(*it)) return true;
	}
	return false;
}

////////////////////////
////// DECODE C

void Instruction::decodeC(bool* code){
	//op code
	code[0]=1;
	code[1]=1;
	code[2]=1;


	std::string dest="";
	for(int i=0; i<Content.size(); i++){
		if (Content[i]=='='){
			dest= std::string(Content, 0, i);
			break;
		}
	}

	std::string jump="";
	for(int i=0; i<Content.size(); i++){
		if (Content[i]==';'){
			jump= std::string(Content, i+1, Content.size()-i-1); 
			break;
		}
	}

	bool hasEqual = dest.size(), hasSemiColom = jump.size();
	std::string comp=std::string(Content, dest.size()+hasEqual, Content.size()-dest.size()-jump.size() - hasEqual - hasSemiColom);

	Instruction::decodeDest(dest, code);
	Instruction::decodeJump(jump, code);
	Instruction::decodeComp(comp, code);
}

////////////////////////
////// DECODE DEST

void Instruction::decodeDest(std::string dest, bool* code){
	for(int i=0; i< destMap.size(); i++){
		if(dest==destMap[i]){
			Instruction::toBinary(i, 3, code+10);
		}
	}
}

////////////////////////
////// DECODE JUMP

void Instruction::decodeJump(std::string jmp, bool* code){
	for(int i=0; i<jumpMap.size(); i++){
		if(jmp==jumpMap[i]){
			Instruction::toBinary(i, 3, code+13);
		}
	}
}

////////////////////////
////// DECODE COMP

void Instruction::decodeComp(std::string comp, bool* code){
	Instruction::toBinary(compMap[comp], 7, code+3);
}

////////////////////////
////// TO BINARY

void Instruction::toBinary(int num, int width, bool* dest){
	for(int i=width-1; i>=0; i--){
		bool bit = num%2;
		dest[i]=bit;
		num -= bit;
		num /= 2;
	}
}