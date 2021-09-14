# Monty
This C program is intended to be an interpreter for monty files
## Description
Monty interpreter designed for use in LINUX. There is a precompilled version called "monty" available or you can compile with all .c files.
### Compilation
```
gcc -Wall -pedantic -Werror -Wextra -std=gnu89 -g *c -o monty
```
### The Monty Language
The Monty language
Monty 0.98 is a scripting language that is first compiled into Monty byte codes (Just like Python). It relies on a unique stack, with specific instructions to manipulate it. The goal of this project is to create an interpreter for Monty ByteCodes files.

#### Monty byte code files

Files containing Monty byte codes usually have the .m extension. Most of the industry uses this standard but it is not required by the specification of the language. There is not more than one instruction per line. There can be any number of spaces before or after the opcode and its argument:
```
julien@ubuntu:~/monty$ cat -e bytecodes/000.m
push 0$
push 1$
push 2$
  push 3$
                   pall    $
push 4$
    push 5    $
      push    6        $
pall$
julien@ubuntu:~/monty$
```
Monty byte code files can contain blank lines (empty or made of spaces only, and any additional text after the opcode or its required argument is not taken into account:
```
julien@ubuntu:~/monty$ cat -e bytecodes/001.m
push 0 Push 0 onto the stack$
push 1 Push 1 onto the stack$
$
push 2$
  push 3$
                   pall    $
$
$
                           $
push 4$
$
    push 5    $
      push    6        $
$
pall This is the end of our program. Monty is awesome!$
julien@ubuntu:~/monty$
```
## Usage
```
	monty <file>
```
<file\> is the path to the file containing Monty byte code
###Errors
All errors will exit with EXIT_FAILURE
```
Error: Can't open file <file>
Error: malloc failed
L<line_number>: unknown instruction <opcode>
```
<file\> is the input file\
<line_number\> is the line of the monty file where the error occurred\
<opcode\> is the attempted input from <line_number\>
### Examples
#### push
Usage: push <int\>
* where int is an integer
* pushes the vaule to the stack
#### pall
Usage: pall
* prints all the values in the stack
* prints nothing if the stack is empty
```
julien@ubuntu:~/monty$ cat -e bytecodes/00.m
push 1$
push 2$
push 3$
pall$
julien@ubuntu:~/monty$ ./monty bytecodes/00.m
3
2
1
julien@ubuntu:~/monty$
```
### pint
Usage: pint
* prints the value at the top of the stack
* returns an error and exits with failure if stack is empty
```
julien@ubuntu:~/monty$ cat bytecodes/06.m
push 1
push 2
push 3
pint
julien@ubuntu:~/monty$ ./monty bytecodes/06.m
3
julien@ubuntu:~/monty$ 
```
Error:
```
L<line_number>: can't pint, stack empty
```
<line_number\> is the line of the monty file where the error occurred
### pop
Usage: pop
* removes the top value of the stack
* returns an error and exits with failure if stack is empty
```
julien@ubuntu:~/monty$ cat bytecodes/07.m 
push 1
push 2
push 3
pall
pop
pall
pop
pall
pop
pall
julien@ubuntu:~/monty$ ./monty bytecodes/07.m 
3
2
1
2
1
1
julien@ubuntu:~/monty$ 
```
Error:
```
L<line_number>: can't pop an empty stack
```
<line_number\> is the line of the monty file where the error occurred
### swap
Usage: swap
* swaps the top two values of the stack
* returns an error and exits with failure if stack has less than two values
```
julien@ubuntu:~/monty$ cat bytecodes/09.m 
push 1
push 2
push 3
pall
swap
pall
julien@ubuntu:~/monty$ ./monty bytecodes/09.m 
3
2
1
2
3
1
julien@ubuntu:~/monty$ 
```
Error
```
L<line_number>: can't swap, stack too short
```
where <line_number\> is the line of the monty file where the error occurred
### Mathmatical Operations
Perform mathmatical operations of the first two values in the stack storing the result in place of the second value and removing the first value

Usage: add
* adds the top two values of the stack

Usage: sub
* subtracts the first value of the stack from the second value of the stack\\

Usage: div
* divides the second value of the stack by the first value of the stack

Usage: mod
* divides the second value of the stack by the first value of the stack and stores the remainder

Usage: mul
* multiples the top two values of the stack

Error:
```
L<line_number>: can't <op>, stack too short
```
<line_number\> is the line of the monty file where the error occurred\
<op\> is the opcode used
### nop
Usage: nop
does nothing
### Comments
Usage: \#
* starting a line with a \# will dennote a comment and will therefore be skipped over
### pchar
Usage: pchar
* prints the char at the top of the stack
* integer stored at the top of the stack is treated as the ascii value of the character to be printed
* fails if the value stored in the top is not an ASCII value
```
julien@ubuntu:~/monty$ cat bytecodes/28.m 
push 72
pchar
julien@ubuntu:~/monty$ ./monty bytecodes/28.m 
H
julien@ubuntu:~/monty$
```
Errors:
```
L<line_number>: can't pchar, value out of range
L<line_number>: can't pchar, stack empty
```
<line_number\> is the line of the monty file where the error occurred
### pstr
Usage: pstr
* prints the string starting at the top of the stack, followed by a new line
* integer stored in each element of the stack is treated as the ascii value of the character to be printed
* The string stops when either:
	- the stack is over
	- the value of the element is 0
	- the value of the element is not in the ascii table
* If the stack is empty, prints only a new line
```
julien@ubuntu:~/monty$ cat bytecodes/31.m 
push 1
push 2
push 3
push 4
push 0
push 110
push 0
push 110
push 111
push 116
push 114
push 101
push 98
push 108
push 111
push 72
pstr
julien@ubuntu:~/monty$ ./monty bytecodes/31.m 
Holberton
julien@ubuntu:~/monty$ 
```
### rotl
Usage: rotl
* rotates the stack to the top
* top element of the stack becomes the last one, and the second top element of the stack becomes the first one
* never fails
```
push 1
push 2
push 3
push 0
pall
rotl
pall
julien@ubuntu:~/monty$ ./monty bytecodes/35.m 
0
3
2
1
3
2
1
0
julien@ubuntu:~/monty$ 
```
### rotr
Usage: rotr
* rotates the stack to the bottom
* last element of the stack becomes the top one, and the second to last element of the stack becomes the last one
* never fails
```
push 1
push 2
push 3
push 0
pall
rotl
pall
julien@ubuntu:~/monty$ ./monty bytecodes/35.m 
0
3
2
1
1
0
3
2
julien@ubuntu:~/monty$ 
```
### stack
Usage: stack
* sets the format of the data to a stack (LIFO)
	- front of a queue becomes the top of the stack
* default behavior of the program
### queue
Usage: queue
* sets the format of the data to a queue (FIFO)
	- top of the stack becomes the front of the queue
```
queue
push 1
push 2
push 3
pall
stack
push 4
push 5
push 6
pall
add
pall
queue
push 11111
add
pall
julien@ubuntu:~/monty$ ./monty bytecodes/47.m
1
2
3
6
5
4
1
2
3
11
4
1
2
3
15
1
2
3
11111
```
## Authors and acknowledgment
Hope Parnell (3251@holbertonschool.com)
## Project status
Complete
