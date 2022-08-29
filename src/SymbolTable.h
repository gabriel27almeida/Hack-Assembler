#ifndef __SYMBOLTABLE__
#define __SYMBOLTABLE__

#include <map>
#include <string>

/*
This class is responsible for maintaining the numerical value of symbols.
Its methods are:

- operator[]. If key is in the table, table[key] returns its numerical value.
Else it adds the key to the table and returns its new value.

- AddKey. Adds a key to the table
*/


class SymbolTable {
public:
	SymbolTable();
	~SymbolTable()=default;

	int operator[](std::string);
	void AddKey(std::string, int);

private:
	std::map<std::string, int> table;
	int var_counter;
};

#endif