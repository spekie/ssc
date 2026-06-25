# Language

SSC supports two statements: `let` to declare a variable and `print` to print an integer expression. Every statement ends with a semicolon. Lines beginning with `//` are treated as comments.

Supported operators are `+`, `-`, `*`, and `/`, with the usual precedence (`*` and `/` bind tighter than `+` and `-`). Parentheses can be used to group expressions. Variables must be declared with `let` before they are used, and cannot be declared twice.

This assembly text data can then be compiled with `gcc` and executed. An example of the language can be found below, as well as a tree showing the process of this conversion.

```
// declare variables
let x = 10;
let y = 2;

// print an expression
print x * y + 5;
```

The above code can be written onto a file with any name or extension, as long as it has text data.
