#include "monty.h"

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
	new_head(stack, n);
}
void pallOp(stack_t **stack, unsigned int line_number)
{
	if(*stack)
		printList(*stack);
	(void)line_number;
}
