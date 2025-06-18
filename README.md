# candle
Low-level, line-based, toy programming language written in C++. It translates .cndl files into intermediate C++ code, which is then compiled into executables using g++.

## Syntax overview:
- The language uses only numbers and each line of code is one statement.
- The first number in the statement is the opcode.
- The remaining number(s) are arguments.
- Comments start with the symbol `@`, comments must inhabit their own separate line of code.

## Currently implemented opcodes:

### Opcode `0` – Return

**Usage:**
`0 <return_argument>`

**Description:**
Returns the return_argument value.


### Opcode `1` – Print

**Usage:**
`1 <ascii_char_argument> [<ascii_char_argument> ...]`

**Description:**
Prints one or multiple characters to the console based on their ASCII values.


### Opcode `2` – User input

**Usage:**
`2`

**Description:**
Requests numerical user input to the console and pushes the value on a numeric stack.


### Opcode `3` – Stack peek

**Usage:**
`3`

**Description:**
Prints the last stack value.


### Opcode `4` – Stack arithmetic

**Usage:**
`4 <arithmetic_operation_argument> <pop_argument>`

**Description:**
Performs an arithmetic operation on the last two numbers in the stack and pushes the result. The arithmetic operation argument can have values from `0` to `4` for basic arithmetic operations (addition, subtraction, multiplication, division) and the modulo operation. The pop argument determines if the operands get popped from the stack afterwards (0 if not, 1 if yes).