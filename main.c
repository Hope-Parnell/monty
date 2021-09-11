#include "monty.h"


void test(void);

char *opCommand[2] = {NULL, NULL};


/**
 * main - main function for monty
 * @ac: argument counter
 * @av: array of argument strings
 *
 * Return: success or failure
 */

int main(int ac, char **av)
{
	FILE *holyGrail;

	if (ac != 2)
	{
		dprintf(STDERR_FILENO, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	holyGrail = fopen(av[1], "r");
	if (!holyGrail)
	{
		dprintf(STDERR_FILENO, "Error: Can't open file %s\n", av[1]);
		exit(EXIT_FAILURE);
	}
	findOpcodes(holyGrail);

	fclose(holyGrail);
	return (EXIT_SUCCESS);

}



void findOpcodes(FILE *holyGrail)
{
	int lineCheck = 0;
	unsigned int line_number;
	size_t opLenth = 0;
	char *opcode = NULL;
	stack_t *stack = NULL;

	for (line_number = 1; lineCheck != EOF; line_number++)
	{
		lineCheck = getline(&opcode, &opLenth, holyGrail);
		opCommand[0] = strtok(opcode, " \n");
		if (!opCommand[0])
			opCommand[0] = strtok(NULL, " \n");
		opCommand[1] = strtok(NULL, " \n");
		checkOpcodes(line_number, &stack);
	}
	if (stack)
		freeList(stack);
	free(opcode);
}

void checkOpcodes(int line_number, 	stack_t **stack)
{
	int i, opCheck = 0;

	instruction_t opFunction[] = {
		{"push", pushOp},
		{"pall", pallOp},
		{"pint", pintOp},
		{"pop", popOp},
		{NULL, NULL}
	};
	for (i = 0; opFunction[i].opcode != NULL; i++)
	{
		if (strcmp(opFunction[i].opcode, opCommand[0]) == 0)
		{	
			opFunction[i].f(stack, line_number);
			opCheck = 1;
			break;
		}
	}
	if (opCheck != 1)
	{
		dprintf(STDERR_FILENO, "L%u: unknown instruction %s\n", line_number, opCommand[0]);
		exit(EXIT_FAILURE);
	}
}
