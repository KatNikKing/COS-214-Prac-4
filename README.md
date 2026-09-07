# TaskForge: Hierarchical Work Processing

## Overview

TaskForge is an emergency response coordination system. The system models an emergency response organisation consisting of response teams and individual responders. Emergencies specify the capabilities and number of responders required, and the system uses these requirements to dispatch suitable response units.

## Requirements

The project is designed to run inside Docker.

The Docker environment provides:

* Ubuntu 24.04
* g++
* make
* GDB
* Valgrind
* C++11 support

## Building the Docker Environment

Clone the repository and navigate to the project directory:

```bash
git clone <https://github.com/KatNikKing/COS-214-Prac-4.git>
cd COS-214-Prac-4
```

Build the Docker image:

```bash
docker build -t taskforge .
```

This builds the project using the supplied `Dockerfile` and `Makefile`.

## Running TaskForge

Run the application inside the Docker container:

```bash
docker run --rm taskforge
```

The program will execute the TaskForge test program and display its output in the terminal.

## GDB Investigation

Start an interactive shell inside the Docker container:

```bash
docker run --rm -it taskforge bash
```

Start GDB:

```bash
gdb ./taskforge
```

For example, to set a breakpoint at `main`:

```gdb
break main
run
```

Useful GDB commands include:

```gdb
next
step
continue
print <variable>
backtrace
quit
```

The executable is compiled with debug information (`-g`), allowing GDB to inspect the program's source code, variables, and execution flow.

Alternatively, the supplied Makefile provides:

```bash
make gdb
```

## Valgrind Investigation

Start an interactive shell inside the Docker container:

```bash
docker run --rm -it taskforge bash
```

Run Valgrind with full leak information:

```bash
valgrind --leak-check=full --show-leak-kinds=all ./taskforge
```

Alternatively, the supplied Makefile provides:

```bash
make valgrind
```

The final application should report no memory that is definitely lost from the project's own code.

## Makefile Commands

The following commands are available when working inside the Docker environment:

```bash
make
```

Builds the TaskForge executable.

```bash
make clean
```

Removes compiled object files and the executable.

```bash
make run
```

Builds and runs TaskForge.

```bash
make gdb
```

Builds the project and starts GDB.

```bash
make valgrind
```

Builds the project and runs Valgrind.

## Compilation

The project is compiled using:

```text
g++ -std=c++11 -g -Wall -Werror
```

This ensures that the project conforms to the required **C++11** standard, includes debugging information, and treats compiler warnings as errors.
