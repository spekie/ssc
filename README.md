# Simple Syntax Compiler (SSC)
> [!NOTE]
> SSC outputs x86-64 Linux assembly. It requires a GNU/Linux system with gcc installed.

This is a small compiler written in C++ to learn more about the process of compiling and assembling code by converting a text file written in a high-level programming language, parsing it and then generate it in the form of assembly code.

## Building

```bash
meson setup build
meson compile -C build
meson install -C build
```

## Documentation

Documentation can be found in the [docs](docs) directory

- [How to use ssc](docs/usage.md)
- [Compiler structure](docs/tree.md)
- [Language syntax](docs/language.md)
