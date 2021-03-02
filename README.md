# Makefile Learning

GitHub: [mmdjiji/makefile-learning](https://github.com/mmdjiji/makefile-learning).

## Introduction

What is makefile? Most Windows developers don't know this, and it is useful in Linux development. Most often, the makefile directs Make on how to compile and link a program.

## Processes of compile
Make sure you have installed [gcc](https://gcc.gnu.org) before learning.

### 1. Preprocessing
Try the following command:
```sh
gcc -E hello.c -o hello.i
```
It means, preprocess only with `hello.c`; do not compile, assemble or link. Then output to `hello.i`.

You can read the output file `hello.i` and try to understand this file.

### 2. Compile
Compile is the most important step, it transform the preprocessing file into an assembly file.
```sh
gcc -S hello.i -o hello.s
```
It means, compile only `hello.i`; do not assemble or link. Then output to `hello.s`, which is an assembly file.

### 3. Assemble
After compiling, you need to assemble it to an object file.

```sh
gcc -c hello.s -o hello.o
```
It means, compile and assemble `hello.s`, but do not link. Then output to `hello.o`, which is an object file.

### 4. Link
The final step is link.
```sh
gcc hello.o -o hello
```

Now you can run this program by the following command:
```sh
./hello
```

## Convenient Compile
You can run the following command without the generation of intermediate file, but the actual process will not change.
```sh
gcc hello.c -o hello
```

## Basic Grammar

### Example
```makefile
# This is a comment.
CC = gcc # variable CC

main: main.c # main rely on main.c
	$(CC) main.c -o main # compile, use variable CC
```

### Symbols
`=` is the most basic assignment;  
`:=` is the value before the override;  
`?=` is the value after the sign if it has not been assigned;  
`+=` is the value after adding the sign.

## Build Rules
```makefile
target: dependencies
	system command(s)
```

* `target` could be an object file, executable file or just a target.
* `dependencies` (also called `prerequisite`) are the file used in the make process. If nothing used, keep empty.
* `system command(s)` (also called `recipe`) is an action that make carries out, usually use shell command.

Example:
```makefile
hello: hello.c
	gcc hello.c -o hello
```

And the example could be also described as follow:
```makefile
hello: hello.o
	gcc hello.o -o hello

hello.o: hello.s
	gcc -c hello.S -o hello.o

hello.s: hello.i
	gcc -S hello.i -o hello.s

hello.i: hello.c
	gcc -E hello.c -o hello.i
```
The order of makefile does not affect the execution results, but for the readability, it is best to use the top-down order.

### Phony Target
There are many advantages to use phony target. One is to avoid the name conflict between the command only target defined in the makefile and the actual file in the working directory; the other is the efficiency of submitting and executing the makefile.

Use `.PHONY` to define the phony target, such as following:
```makefile
.PHONY: clean
```
The `.PHONY` can define more than one target:
```makefile
.PHONY: clean install

clean:
	rm -rf *.o

install:
	cp hello /usr/local/bin
```

## Multi Build
If you have two targets or more to build, you may try to write as follows:
```makefile
main_a: main_a.c
	gcc main_a.c -o main_a

main_b: main_b.c
	gcc main_b.c -o main_b
```
This cannot help you compile two targets or more, if you check the built files, you won't see `main_b`. The reason is that makefile only processes the top one, and `main_a` doesn't rely on `main_b`, so `main_b` won't be built.

The solution is use `all:`, like follows:
```makefile
.PHONY: all

all: main_a main_b

main_a: main_a.c
	gcc main_a.c -o main_a

main_b: main_b.c
	gcc main_b.c -o main_b
```
Now `all` become the top one, and it rely on `main_a` and `main_b`, so all targets will be built.

## Abstract Build
If the compiler now instead of `gcc`, we use `g++`, `clang` or `clang++`, and we don't want to change every `gcc` because it is too trouble. We can use abstract build to solve the problem.

We can define a variable `CC = gcc`, and use it by using `$(CC)` later.
```makefile
CC = gcc

main: main.c
	$(CC) main.c -o main
```

Then, we can use more and more variable to abstract this file.
```makefile
TAR = abstract
OBJ = main.o
CC = gcc

$(TAR): $(OBJ)
	$(CC) $(OBJ) -o $(TAR)

main.o: main.c
	$(CC) -c main.c -o main.o

.PHONY: clean

clean:
	${RM} $(OBJ)
```

## Batch Build
Use the pattern rules can help you batch build:
* `$@`: Target files.
* `$^`: Dependencies files.
* `$<`: First dependency file.
* `$%`: When the target file is a static library file, it represents a member name of the static library.
* `$?`: A list of all dependent files that are newer than the target file, separated by spaces. If the target file is a static library file, it represents a library file(`.o`).

Example:
```makefile
TAR = batch
OBJ = alpha.o bravo.o charlie.o delta.o main.o
CC = gcc

$(TAR): $(OBJ)
	$(CC) $^ -o $@

%.o: %.c
	$(CC) -c $^ -o $@
```

## VPATH
If the source code in the folder but not the current directory, you may use `VPATH`:
```makefile
VPATH := src
```
It means the source code in the `src` folder.

If you want to define more than one `VPATH`, use follows:
```makefile
VPATH := src1 src2
```

## vpath
Selective search files from a directory.

Usage:
```makefile
vpath PATTERN DIRECTORIES
```

Example:
```makefile
vpath %.c src tester/src
```

Clean the vpath for %.c:
```makefile
vpath %.c
```

Clean the vpath for all:
```makefile
vpath
```

## Include
Include other makefile:
```makefile
include <filenames>
```

When the included file doesn't exist or there are no rules to create it, if you want make will continue to execute the program (Only when the ultimate goal reconstruction can't be completed, our program will prompt error save and exit.), you can use follows:
```makefile
-include <filenames>
```

## License
All documents use [CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/) license, all codes use [GNU GPLv3](https://choosealicense.com/licenses/gpl-3.0/).