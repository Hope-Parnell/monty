#ifndef MONTY_H
#define MONTY_H


#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stddef.h>
#include <fcntl.h>

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO Holberton project
 */
typedef struct stack_s
{
		int n;
		struct stack_s *prev;
		struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO Holberton project
 */
typedef struct instruction_s
{
		char *opcode;
		void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

/*main*/
void findOpcodes(FILE *holyGrail);
void checkOpcodes(int line_number, stack_t **stack);
/*linkedList*/
stack_t *new_head(stack_t **head, const int n);
size_t printList(const stack_t *h);
void freeList(stack_t *head);
stack_t *new_tail(stack_t **head, const int n);
/*ops1*/
void pushOp(stack_t **stack, unsigned int line_number);
void pallOp(stack_t **stack, unsigned int line_number);
void pintOp(stack_t **stack, unsigned int line_number);
void popOp(stack_t **stack, unsigned int line_number);
void swapOp(stack_t **stack, unsigned int line_number);
/*ops2*/
void addOp(stack_t **stack, unsigned int line_number);
/*advanced*/
void subOp(stack_t **stack, unsigned int line_number);
void divOp(stack_t **stack, unsigned int line_number);
void modOp(stack_t **stack, unsigned int line_number);
void mulOp(stack_t **stack, unsigned int line_number);
/*ops3*/
void pcharOp(stack_t **stack, unsigned int line_number);
void pstrOp(stack_t **stack, unsigned int line_number);
void rotlOp(stack_t **stack, unsigned int line_number);
void rotrOp(stack_t **stack, unsigned int line_number);
void stackQOp(stack_t **stack, unsigned int line_number);

extern char *opCommand[];

#endif /*MONTY_H*/
