# Simple Syntax Compiler (SSC)
> [!NOTE]
> SSC outputs x86-64 Linux assembly. It requires a GNU/Linux system with gcc installed.

This is a small compiler written in C++ to learn more about the process of compiling and assembling code by converting a text file written in a high-level programming language, parsing it and then generate it in the form of assembly code.

This assembly can then be compiled with `gcc` and executed. An example of the language can be found below, as well as a tree showing the process of this conversion.

## Building

```bash
make
```

Install to `/usr/local/bin`

```bash
sudo make clean install
```

## Language

SSC supports two statements: `let` to declare a variable and `print` to print an integer expression. Every statement ends with a semicolon. Lines beginning with `//` are treated as comments.

Supported operators are `+`, `-`, `*`, and `/`, with the usual precedence (`*` and `/` bind tighter than `+` and `-`). Parentheses can be used to group expressions. Variables must be declared with `let` before they are used, and cannot be declared twice.

```
// declare variables
let x = 10;
let y = 2;

// print an expression
print x * y + 5;
```

The above code can be written onto a file with any name or extension, as long as it has text data.

## Usage

This code is then compiled and the compiler outputs the code in the assembly language:

```bash
ssc test 
```

Pass the file to `ssc` and redirect the output into a `.s` file:

```bash
ssc test > out.s
```

The assembly code can be compiled with gcc:

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
Code generation (Codegen) ---> Linux x86-64 Assembly Output
```
