#include "monty.h"

/**
 * pushOp - performs the push opcode
 * @stack: doubly linked list containing the stack
 * @line_number: line number the opcode came from
 */

void pushOp(stack_t **stack, unsigned int line_number)
{
	int n;

	if (!opCommand[1])
	{
		dprintf(STDERR_FILENO, "L%u: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}
	n = atoi(opCommand[1]);
	if (n == 0 && opCommand[1][0] != '0')
	{
		dprintf(STDERR_FILENO, "L%u: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}
	if (strcmp("queue", opCommand[2]) == 0)
		new_tail(stack, n);
	else
		new_head(stack, n);
}

/**
 * pallOp - performs the pall opcode
 * @stack: doubly linked list containing the stack
 * @line_number: line number the opcode came from
 */

void pallOp(stack_t **stack, unsigned int line_number)
{
	if (*stack)
		printList(*stack);
	(void)line_number;
}

/**
 * pintOp - performs the pint opcode
 * @stack: doubly linked list containing the stack
 * @line_number: line number the opcode came from
 */

void pintOp(stack_t **stack, unsigned int line_number)
{
	stack_t *seek;

	if (!*stack)
	{
		dprintf(STDERR_FILENO, "L%u: can't pint, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}
	seek = *stack;
	while (seek->prev)
		seek = seek->prev;
	printf("%i\n", seek->n);
}

/**
 * popOp - performs the pop opcode
 * @stack: doubly linked list containing the stack
 * @line_number: line number the opcode came from
 */

void popOp(stack_t **stack, unsigned int line_number)
{
	stack_t *hide;

	if (!*stack)
	{
		dprintf(STDERR_FILENO, "L%u: can't pop an empty stack\n", line_number);
		exit(EXIT_FAILURE);
	}
	hide = *stack;
	while (hide->prev)
		hide = hide->prev;
	if (hide->next)
		hide->next->prev = NULL;
	if (hide == *stack)
	{
		if ((*stack)->next)
			*stack = (*stack)->next;
		else
			*stack = NULL;
	}
	free(hide);
}

/**
 * swapOp - performs the swap opcode
 * @stack: doubly linked list containing the stack
 * @line_number: line number the opcode came from
 */

void swapOp(stack_t **stack, unsigned int line_number)
{
	stack_t *seek, *swap;

	if (!*stack || (((!(*stack)->prev)) && (!(*stack)->next)))
	{
		dprintf(STDERR_FILENO, "L%u: can't swap, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	for (seek = *stack; seek->prev; seek = seek->prev)
	;
	swap = seek->next;
	if (swap->next)
		seek->next = swap->next;
	else
		seek->next = NULL;
	swap->prev = NULL;
	swap->next = seek;
	seek->prev = swap;
}
