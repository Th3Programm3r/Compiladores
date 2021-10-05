# Compiladores
Application using c language, this project had the goal to receive a code in c language, and convert to assembly mips language.

## PrintInstr
To run the application you need first to run in the terminal the command make, after that you need to create a txt file having inside
the c code to be compiled to mips, then you execute the command ./printInstr <name of the txt file created before>.txt, in the end the 
result converted mips code will be in a file named mips.asm.
The application first receives the c code defined in the txt file, then it converts to pcode that is defined on the file stack.h and the
p codes instructions are implemented in the file stack.c, and after converting to pcode it writes the code to a file named mips.asm.

## PrintAbsTree
  
It has also implemented a function that prints a tree corresponding to the c code
