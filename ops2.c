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
		dprintf(STDERR_FILENO, "L%u: can't swap, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	for (hide = *stack; hide->prev; hide = hide->prev)
	;
	seek = hide->next;
	seek->n = seek->n + hide->n;
	seek->prev = NULL;
	free(hide);
}
