#include "monty.h"

/**
 * pushOp - performs the push opcode
 * @stack: doubly linked list containing the stack
 * @line_number: line number the opcode came from
 */

void pushOp(stack_t **stack, unsigned int line_number)
{
	int n;

	if (!opCommand[1])/*push had no argument*/
	{
		dprintf(STDERR_FILENO, "L%u: usage: push integer\n", line_number);
		opCommand[3] = "ERROR";
		return;
	}
	for (n = 0; opCommand[1][n] != '\0'; n++)
	{
		if ((opCommand[1][n] == '-' && n == 0) || (opCommand[1][n] == '.'))
			n++;/*go to next char to check for a digit*/
		if (!isdigit(opCommand[1][n]))
		{
			dprintf(STDERR_FILENO, "L%u: usage: push integer\n", line_number);
			opCommand[3] = "ERROR";
			return;
		}
	}
	n = atoi(opCommand[1]);
	if (strcmp("queue", opCommand[2]) == 0)/*program is currently a queue*/
	{/*add to end*/
		if (new_tail(stack, n) == NULL)
		opCommand[3] = "ERROR";
		return;
	}
	else/*program is currently a stack*/
	{/*add to begining*/
		if (new_head(stack, n) == NULL)
		{
			opCommand[3] = "ERROR";
			return; }
	}
}

/**
 * pallOp - performs the pall opcode
 * @stack: doubly linked list containing the stack
 * @line_number: line number the opcode came from
 */

void pallOp(stack_t **stack, unsigned int line_number)
{
	stack_t *seek, *head;
	size_t nodes;

	if (!*stack)/*check if list is NULL*/
		return;
	head = *stack;
	while (head->prev) /*find the head*/
		head = head->prev;
	seek = head;
	for (nodes = 0; seek != NULL; nodes++)/*increment nodes until NULL*/
	{
		printf("%d\n", seek->n);/*print each integer*/
		seek = seek->next;
	}
	return;
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

	if (!*stack)/*there is no stack*/
	{
		dprintf(STDERR_FILENO, "L%u: can't pint, stack empty\n", line_number);
		opCommand[3] = "ERROR";
		return;
	}
	seek = *stack;
	while (seek->prev)/*find the top*/
		seek = seek->prev;
	printf("%i\n", seek->n);/*print the value*/
}

/**
 * popOp - performs the pop opcode
 * @stack: doubly linked list containing the stack
 * @line_number: line number the opcode came from
 */

void popOp(stack_t **stack, unsigned int line_number)
{
	stack_t *hide;

	if (!*stack)/*there is no stack*/
	{
		dprintf(STDERR_FILENO, "L%u: can't pop an empty stack\n", line_number);
		opCommand[3] = "ERROR";
		return;
	}
	hide = *stack;
	while (hide->prev)/*find the top*/
		hide = hide->prev;
	if (hide->next) /*makes next node top*/
		hide->next->prev = NULL;
	if (hide == *stack)
	{/*makes sure we retain access to list*/
		if ((*stack)->next)/*there is a second node*/
			*stack = (*stack)->next;
		else/*there are no more nodes*/
			*stack = NULL;
	}
	free(hide);/*free the top node*/
}

/**
 * swapOp - performs the swap opcode
 * @stack: doubly linked list containing the stack
 * @line_number: line number the opcode came from
 */

void swapOp(stack_t **stack, unsigned int line_number)
{
	stack_t *seek, *swap;
	int n;

	if (!*stack || (((!(*stack)->prev)) && (!(*stack)->next)))
	{/*there are less than 2 nodes*/
		dprintf(STDERR_FILENO, "L%u: can't swap, stack too short\n", line_number);
		opCommand[3] = "ERROR";
		return;
	}
	for (seek = *stack; seek->prev; seek = seek->prev)
	;/*find the top*/
	swap = seek->next;
	n = seek->n;
	seek->n = swap->n;
	swap->n = n;
}
