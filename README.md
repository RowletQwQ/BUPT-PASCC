# PASCC

A Compiler that compile Pascal-S to C/RISC-V

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
|   |-- parser # Parser (flex + bison)
|   |-- ast # Abstract Syntax Tree
|   |-- common # tools
|   |-- ir # Intermediate Representation And Semantic Analysis
|   |-- builder # Code Generator
|   |-- opt # Optimizer
|-- test # Test
```

## Building Docker Image

To build the docker image, run the following command.
It will build the docker image with the name `my-riscv-env`.
```bash
docker build -t my-riscv-env . --network=host
```

To run the docker image, run the following command.
It will run the docker image with the name `my-riscv-env`.
```bash
docker run -it --name my-riscv-env --mount type=bind,src=[absolute path of folder in host machine],dst=[absolute path in container] my-riscv-env /bin/bash
```