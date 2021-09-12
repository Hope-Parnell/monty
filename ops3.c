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
		exit(EXIT_FAILURE);
	}
	for (seek = *stack; seek->prev; seek = seek->prev)
	;
	if ((seek->n < 0) || (seek->n > 127))
	{
		dprintf(STDERR_FILENO, "L%u: can't pchar, value out of range\n",
					 line_number);
		exit(EXIT_FAILURE);
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
