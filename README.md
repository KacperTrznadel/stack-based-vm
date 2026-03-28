# Stack-Based Virtual Machine

This project is an implementation of a custom stack-based virtual machine that executes a symbolic instruction language.
The VM operates on a stack of dynamically sized character lists, which can represent both symbolic data and integer values.


## Overview

The virtual machine consists of:
- **Program memory** - a sequence of single-character instructions
- **Instruction pointer** - controls execution flow
- **Stack** - stores lists of characters representing data

Each instruction modifies the state of the stack or affects control flow.


## Full list of Single-Character Instructions

|  Instruction |                                                            Description                                                            |
| ------------ | --------------------------------------------------------------------------------------------------------------------------------- |
|       '      |                                                 Push an empty list onto the stack.                                                |
|       ,      |                                               Remove the top element from the stack.                                              |
|       :      |                                                  Duplicate the top stack element.                                                 |
|       ;      |                                                  Swap the top two stack elements.                                                 |
|       @      |                      Pop the number A off the stack and then push a copy of the element at index A (0 = top).                     |
|       .      |                           Read a character from standard input and prepend it to the top stack element.                           |
|       >      |                                Output the first character of the top stack element and pop it off.                                |
|       !      |                            Replace the top stack element with logical NOT ('0' -> '1', otherwise '0').                            |
|       <      |                                   Pop A and B off the stack, compare B < A and push '1' or '0'.                                   |
|       =      |                                   Pop A and B off the stack, compare B = A and push '1' or '0'.                                   |
|       ~      |                                       Push current instruction pointer value onto the stack.                                      |
|       ?      | Pop J and C; if C is true, jump to instruction J. |
|       -      |                                               Toggle sign of the top stack element.                                               |
|       ^      |                                       Remove sign of the top stack element (absolute value).                                      |
|       $      |                         Detach the first character of the top stack element and create a new one from it.                         |
|       #      |                                 Pop the top stack element and append it into the new top element.                                 |
|       +      |                                             Pop A and B off the stack and push A + B.                                             |
|       &      |                                                    Print the entire stack.                                                    |
|       ]      |                       Pop a number off the stack, convert it into ASCII character and push it onto the stack.                       |
|       [      |                       Pop a character off the stack, convert it into ASCII number and push it onto the stack.                       |
|     other    |                                               Prepend character to the top element.                                               |


## Example Programs

### 1. Arithmetic operations

**Program:**

```
'123'-456&+&
```

**Output:**

```
1: 321
0: 654-
0: 333-
```

---

### 2. Input handling and stack manipulation

**Program:**

```
'...&$&
```

**Input:**

```
123
```

**Output:**

```
0: 321
1: 21
0: 3
```

---

### 3. Conditional jump:

**Program:**

```
'3'3='13?'abc'def&
```

**Output:**

```
0: fed
```

## Design Notes

The VM represents all data as linked lists of characters, allowing uniform handling of both symbolic data and arbitrary-length integers.

Due to strict constraints (no STL containers and minimal array and loop usage), most operations are implemented recursively, which significantly influenced the overall design.

This project demonstrates low-level data structure design, execution models and interpreter-like architecture.
