#include "Parser.h"

////////////////////////
////// CONSTRUCTOR

Parser::Parser(std::string fileName_, SymbolTable* t){
	fileName = fileName_;
	File.open(fileName_);
	PC=-1;
	table = t;
}

////////////////////////
////// DECONSTRUCTOR

Parser::~Parser(){
	File.close();
}

////////////////////////
////// ADVANCE

bool Parser::Advance(bool firstPassage){
	while(! File.eof()){
		std::string s;
		getline(File, s);

		// remove white space
		s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());

		// if white space or comment 
		if(s.empty() || s[0]=='/') continue;

		// if label declaration 
		if(!firstPassage && s[0]=='(') continue;

		// remove inline comment
		for(auto it=s.begin(); it!=s.end(); it++){
			if (*it=='/'){
				s.erase(it, s.end());
				break;
			}
		}

		CurrentInstruction = s;
		PC++;
		return 1;
	}
	return 0;
}

////////////////////////
////// GET INSTRUCTION

std::string Parser::GetInstruction(){
	return CurrentInstruction;
}

////////////////////////
////// GET PC

int Parser::GetPC(){
	return PC;
}

////////////////////////
////// FIRST PASSAGE

void Parser::FirstPassage(){
	while(this->Advance(true)){
		if(CurrentInstruction[0]=='('){
			table->AddKey(std::string(CurrentInstruction, 1, CurrentInstruction.size()-2), PC);
			PC--;
		}
	}
}

////////////////////////
////// RESET

void Parser::Reset(){
	PC=-1;
	File.close();
	File.open(fileName);
}