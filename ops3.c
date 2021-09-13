#include "monty.h"

/**
 * pcharOp - performs the pchar opcode
 * @stack: doubly linked list containing the stack
 * @line_number: line number the opcode came from
 */

void pcharOp(stack_t **stack, unsigned int line_number)
{
	stack_t *seek;

	if (!*stack)
	{
		dprintf(STDERR_FILENO, "L%u: can't pchar, stack empty\n", line_number);
		opCommand[3] = "ERROR";
		return;
	}
	for (seek = *stack; seek->prev; seek = seek->prev)
	;
	if ((seek->n < 0) || (seek->n > 127))
	{
		dprintf(STDERR_FILENO, "L%u: can't pchar, value out of range\n",
					 line_number);
		opCommand[3] = "ERROR";
		return;
	}
	printf("%c\n", seek->n);
}

/**
 * pstrOp - performs the pstr opcode
 * @stack: doubly linked list containing the stack
 * @line_number: line number the opcode came from
 */

void pstrOp(stack_t **stack, unsigned int line_number)
{
	stack_t *seek;

	if (*stack)
	{
		for (seek = *stack; seek->prev; seek = seek->prev)
		;
		while (seek)
		{
			if ((seek->n <= 0) || (seek->n > 127))
				break;
			putchar(seek->n);
			seek = seek->next;
		}
	}
	putchar('\n');
	(void)line_number;
}

/**
 * rotlOp - performs the rotl opcode
 * @stack: doubly linked list containing the stack
 * @line_number: line number the opcode came from
 */

void rotlOp(stack_t **stack, unsigned int line_number)
{
	stack_t *first, *last;

	if (!*stack)
		return;
	for (first = *stack; first->prev; first = first->prev)
	;
	for (last = *stack; last->next != NULL; last = last->next)
	;
	if (first == last)
		return;
	if (first == *stack)
		*stack = first->next;
	first->next->prev = NULL;
	first->next = NULL;
	first->prev = last;
	last->next = first;
	(void)line_number;
}

/**
 * rotrOp - performs the rotr opcode
 * @stack: doubly linked list containing the stack
 * @line_number: line number the opcode came from
 */

void rotrOp(stack_t **stack, unsigned int line_number)
{
	stack_t *first, *last;

	if (!*stack)
		return;
	for (first = *stack; first->prev; first = first->prev)
	;
	for (last = *stack; last->next != NULL; last = last->next)
	;
	if (first == last)
		return;
	last->prev->next = NULL;
	last->prev = NULL;
	first->prev = last;
	last->next = first;
	(void)line_number;
}

/**
 * stackQOp - performs the stack/queue opcodes
 * @stack: doubly linked list containing the stack
 * @line_number: line number the opcode came from
 */

void stackQOp(stack_t **stack, unsigned int line_number)
{
	if (strcmp(opCommand[0], "stack") == 0)
		opCommand[2] = "stack";
	if (strcmp(opCommand[0], "queue") == 0)
		opCommand[2] = "queue";
	(void)stack;
	(void)line_number;
}
