#include "monty.h"

/**
 * main - main function for monty
 * @ac: argument counter
 * @av: array of argument strings
 *
 * Return: success or failure
 */

int main(int ac, char **av)
{
	int monty;
	if (ac != 2)
	{	
		dprintf(STDERR_FILENO, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	monty = open(av[1], O_RDONLY);
	if (monty < 0)
	{
		dprintf(STDERR_FILENO, "Error: Can't open file %s\n", av[1]);
		exit (EXIT_FAILURE);
	}

	return (EXIT_SUCCESS);

}
