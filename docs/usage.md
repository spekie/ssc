# Usage

Compile the [test](test) file and the compiler outputs the code in the assembly language:

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
