# Simple Shell

<p align="center">
  <img src="./imgs/0_Qqqd7UsfFDPL7WXh.jpg" alt="Linux Shell Illustration" />
</p>

## Overview

This project implements a simple shell with essential features inspired by the Bash shell. It is designed to demonstrate fundamental concepts of shell programming using C. The shell supports basic commands, chaining, aliasing, and dynamic handling of environment variables.

## Features

### Core Functionality
- **Execution of Bash Commands**
  - Execute standard Bash commands directly within the shell.

- **Command Chaining**
  - Support for chaining commands using `;`.

- **Aliasing**
  - Define and use command aliases for convenience.

- **Environment Variable Management**
  - View, set, and modify environment variables dynamically.

### Built-in Functions
- Many standard library functions in C have been replaced with custom-built versions to demonstrate proficiency and provide a tailored shell experience.
- The project uses a linked list to handle dynamic environment variable management efficiently.

## Installation and Usage

### Compilation
To compile the shell, run the following command in your terminal:
```bash
gcc *.c -o shell
```

### Running the Shell
Once compiled, you can run the shell with:
```bash
./shell
```

## Additional Notes
- The shell is implemented entirely in C.
- It emphasizes simplicity, efficiency, and a clear demonstration of fundamental concepts like process management and memory handling.

This project was built during my study in ALX Software Engineering Program.