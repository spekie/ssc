# Simple Syntax Compiler (SSC)

This is a small compiler written in C++ to learn more about the process of compiling and assembling code by converting a text file written in a high-level programming language, parsing it and then generate it in the form of assembly code.

This code can then be assembled and executed it, an example of this simple code can be found below, as well as a tree showing the process of this conversion.

## Example
```
let x = 10;
let y = 2;
print x * y + 5;
```
The above code can be written onto a file with any name or extension, as long as it has text data.

```bash
ssc test 
```
This code is then compiled and the compiler outputs the code in the assembly language.

```bash
ssc test > out.s
```
The assembly code can be outputted into another file and then compiled with gcc.
```bash
gcc out.s
```

## Tree
```
Source Code
   |
Lexer ---> Tokens
   |
Parser ---> Abstract Syntax Tree (AST)
   |
Code generation (Codegen) ---> Pseudo-Assembly Output
```
