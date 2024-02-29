# PASCC

A Compiler that compile Pascal to C

## Run

First, make directory `build` and `bin` in the root directory of the project.

```bash
mkdir build && mkdir bin
```

Then, run the following commands to compile the project.

```bash
cd build
cmake .. && make
```

After that, you can run the compiler with the following command.

```bash
./bin/pascc -i <input_file>
```

## File Structure

```
.
|-- src # Source code
|   |-- main.cpp # Main function
|   |-- parser # Parser
|   |   |-- stmt.hpp # Statement
|   |-- common # tools
|   |-- ir # Intermediate Representation(中间表示形式相关)
|   |-- generator # Code Generator

