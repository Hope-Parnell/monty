#include "monty.h"

/**
 * addOp - performs the add opcode
 * @stack: doubly linked list containing the stack
 * @line_number: line number the opcode came from
 */

void addOp(stack_t **stack, unsigned int line_number)
{
	stack_t *seek, *hide;

	if (!*stack || (((!(*stack)->prev)) && (!(*stack)->next)))
	{
		dprintf(STDERR_FILENO, "L%u: can't add, stack too short\n", line_number);
		opCommand[4] = "ERROR";
		return;
	}
	for (hide = *stack; hide->prev; hide = hide->prev)
	;
	seek = hide->next;
	seek->n = hide->n + seek->n;
	seek->prev = NULL;
	free(hide);
}

/**
 * subOp - performs the sub opcode
 * @stack: doubly linked list containing the stack
 * @line_number: line number the opcode came from
 */

void subOp(stack_t **stack, unsigned int line_number)
{
	stack_t *seek, *hide;

	if (!*stack || (((!(*stack)->prev)) && (!(*stack)->next)))
	{
		dprintf(STDERR_FILENO, "L%u: can't sub, stack too short\n", line_number);
		opCommand[4] = "ERROR";
		return;
	}
	for (hide = *stack; hide->prev; hide = hide->prev)
	;
	seek = hide->next;
	seek->n = seek->n - hide->n;
	seek->prev = NULL;
	free(hide);
}

/**
 * divOp - performs the sub opcode
 * @stack: doubly linked list containing the stack
 * @line_number: line number the opcode came from
 */

void divOp(stack_t **stack, unsigned int line_number)
{
	stack_t *seek, *hide;

	if (!*stack || (((!(*stack)->prev)) && (!(*stack)->next)))
	{
		dprintf(STDERR_FILENO, "L%u: can't div, stack too short\n", line_number);
		opCommand[4] = "ERROR";
		return;
	}
	for (hide = *stack; hide->prev; hide = hide->prev)
	;
	if (hide->n == 0)
	{
		dprintf(STDERR_FILENO, "L%u: division by zero\n", line_number);
		opCommand[4] = "ERROR";
		return;
	}
	seek = hide->next;
	seek->n = seek->n / hide->n;
	seek->prev = NULL;
	free(hide);
}

/**
 * modOp - performs the sub opcode
 * @stack: doubly linked list containing the stack
 * @line_number: line number the opcode came from
 */

void modOp(stack_t **stack, unsigned int line_number)
{
	stack_t *seek, *hide;

	if (!*stack || (((!(*stack)->prev)) && (!(*stack)->next)))
	{
		dprintf(STDERR_FILENO, "L%u: can't mod, stack too short\n", line_number);
		opCommand[4] = "ERROR";
		return;
	}
	for (hide = *stack; hide->prev; hide = hide->prev)
	;
	if (hide->n == 0)
	{
		dprintf(STDERR_FILENO, "L%u: division by zero\n", line_number);
		opCommand[4] = "ERROR";
		return;
	}
	seek = hide->next;
	seek->n = seek->n % hide->n;
	seek->prev = NULL;
	free(hide);
}

/**
 * mulOp - performs the sub opcode
 * @stack: doubly linked list containing the stack
 * @line_number: line number the opcode came from
 */

void mulOp(stack_t **stack, unsigned int line_number)
{
	stack_t *seek, *hide;

	if (!*stack || (((!(*stack)->prev)) && (!(*stack)->next)))
	{
		dprintf(STDERR_FILENO, "L%u: can't mul, stack too short\n", line_number);
		opCommand[4] = "ERROR";
		return;
	}
	for (hide = *stack; hide->prev; hide = hide->prev)
	;
	seek = hide->next;
	seek->n = seek->n * hide->n;
	seek->prev = NULL;
	free(hide);
}
