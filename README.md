# Hack-Assembler
Hack machine language assembler (Project nand2tetris)

This assembler was a task of the project "Building a Computer from First Principles", also known as [nand2tetris](https://www.nand2tetris.org/).

### Usage

To create the `HackAssembler` executable, execute the command 
```
g++ main/HackAssembler.cpp src/Parser.cpp src/Instruction.cpp src/SymbolTable.cpp -o HackAssembler -std=c++11 -I src
```

To assemble a `.asm` file, simply execute `./HackAssembler file_name.asm`. 

A `file_name.hack` will be created (or overwritten), which the HACK computer can read and execute.