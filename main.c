#include "monty.h"

char *opCommand[] = {NULL, NULL, "stack", NULL};

/**
 * main - main function for monty
 * @ac: argument counter
 * @av: array of argument strings
 *
 * Return: success or exit with failure
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

	if (fclose(holyGrail) != 0)
		exit(EXIT_FAILURE);
	if (opCommand[3])
		exit(EXIT_FAILURE);
	return (EXIT_SUCCESS);

}

/**
 * findOpcodes - checks the file line by line for opcodes
 * @holyGrail: file stream of the input file
 */

void findOpcodes(FILE *holyGrail)
{
	int lineCheck = 0, i;
	unsigned int line_number;
	size_t opLenth = 0;
	char *opcode = NULL;
	stack_t *stack = NULL;

	for (line_number = 1; ; line_number++)
	{
		lineCheck = getline(&opcode, &opLenth, holyGrail);
		if (lineCheck == EOF)
			break;
		if (lineCheck == 1)
			continue;
		for (i = 0; opcode[0] != '\0'; i++)
		{
			if (opcode[i] == '\n' || lineCheck == 1)
				break;
			if (opcode[i] == ' ' || opcode[i] == '\t')
				lineCheck = 1;
			else
				lineCheck = 0;
		}
		if (lineCheck == 1)
			continue;
		opCommand[0] = strtok(opcode, " \n\t\0");
		if (!opCommand[0])
			opCommand[0] = strtok(NULL, " \n\t\0");
		if (opCommand[0][0] == '#')
			continue;
		opCommand[1] = strtok(NULL, " \n\t\0");
		checkOpcodes(line_number, &stack);
		if (opCommand[3])
			break;
	}
	if (stack)
		freeList(stack);
	free(opcode);
}

/**
 * checkOpcodes - checks for and runs the opcode
 * @line_number: line number the opcode came from
 * @stack: doubly linked list of the stack
 */

void checkOpcodes(int line_number, stack_t **stack)
{
	int i, opCheck = 0;

	instruction_t opFunction[] = {
		{"push", pushOp},
		{"pall", pallOp},
		{"pint", pintOp},
		{"pop", popOp},
		{"swap", swapOp},
		{"add", addOp},
		{"sub", subOp},
		{"div", divOp},
		{"mod", modOp},
		{"mul", mulOp},
		{"pchar", pcharOp},
		{"pstr", pstrOp},
		{"rotl", rotlOp},
		{"rotr", rotrOp},
		{"stack", stackQOp},
		{"queue", stackQOp},
		{"nop", NULL},
		{NULL, NULL}
	};
	for (i = 0; opFunction[i].opcode != NULL; i++)
	{
		if (strcmp(opFunction[i].opcode, opCommand[0]) == 0)
		{
			if (opFunction[i].f)
				opFunction[i].f(stack, line_number);
			opCheck = 1;
			break;
		}
	}
	if (opCheck != 1)
	{
		dprintf(STDERR_FILENO, "L%u: unknown instruction %s\n",
				 line_number, opCommand[0]);
		opCommand[3] = "ERROR";
		return;
	}
}
