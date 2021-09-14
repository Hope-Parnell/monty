#include "monty.h"

char *opCommand[] = {NULL, NULL, "stack", NULL};

/**
 * main - main function for monty
 * @ac: argument counter
 * @av: array of argument strings
 *
 * Return: success exit with failure
 */

int main(int ac, char **av)
{
	FILE *holyGrail;

	if (ac != 2)/*check for correct usage*/
	{
		dprintf(STDERR_FILENO, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	holyGrail = fopen(av[1], "r");
	if (!holyGrail)/*check if file could open*/
	{
		dprintf(STDERR_FILENO, "Error: Can't open file %s\n", av[1]);
		exit(EXIT_FAILURE);
	}
	findOpcodes(holyGrail);/*search through the file for opcodes*/

	if (fclose(holyGrail) != 0)/*close the file*/
		exit(EXIT_FAILURE);
	if (opCommand[3])/*An error occurred*/
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
		if (lineCheck == EOF)/*getline failed*/
			break;
		if (lineCheck == 1)/*There is only a newline*/
			continue;
		for (i = 0; opcode[0] != '\0'; i++)
		{
			if (opcode[i] == '\n' || lineCheck == 1)
				break;/*got to end of line or found a possible code*/
			if (opcode[i] == ' ' || opcode[i] == '\t')
				lineCheck = 0;
			else /*there is a possible code*/
				lineCheck = 1;
		}
		if (lineCheck == 0)
			continue;/*there were only spaces or tabs*/
		opCommand[0] = strtok(opcode, " \n\t");
		if (!opCommand[0])/*line starts with spaces or tabs*/
			opCommand[0] = strtok(NULL, " \n\t");
		if (opCommand[0][0] == '#')
			continue;/*line is a comment*/
		opCommand[1] = strtok(NULL, " \n\t");
		checkOpcodes(line_number, &stack);/*match input to opcodes*/
		if (opCommand[3])/*an error occurred*/
			break;
	}
	if (stack)/*free the stack*/
		freeList(stack);
	if (opcode)/*free the buffer*/
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
	{/*input matches an opcode*/
		if (strcmp(opFunction[i].opcode, opCommand[0]) == 0)
		{
			if (opFunction[i].f)
				opFunction[i].f(stack, line_number);
			if (opCommand[3])/*an error occurred*/
				return;
			opCheck = 1;/*an opcode successfully ran*/
			break; }
	}
	if (opCheck != 1)/*input did not match any opcodes*/
	{
		dprintf(STDERR_FILENO, "L%u: unknown instruction %s\n",
				 line_number, opCommand[0]);
		opCommand[3] = "ERROR";
		return; }
}
