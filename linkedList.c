#include "monty.h"

/**
 * new_head - adds a node to the beginning of doubly linked list
 *
 * @head: pointer to the list
 * @n: integer value to store in the node
 * Return: pointer to the new node;
 */

stack_t *new_head(stack_t **head, const int n)
{
	stack_t *new, *trueHead;

	new = malloc(sizeof(stack_t));
	if (!new)
	{
		dprintf(STDERR_FILENO, "Error: malloc failed");
		putchar('\n');
		opCommand[4] = "ERROR";
		return (NULL);
	}
	new->prev = NULL;
	new->n = n;
	if (!*head)/*check if list is empty*/
	{
		new->next = NULL;
		*head = new;
	}
	else
	{
		trueHead = *head;
		while (trueHead->prev)/*make sure at actual head*/
			trueHead = trueHead->prev;
		new->next = trueHead;
		trueHead->prev = new;
	}
	return (new);
}

/**
 * printList - prints the contents of a doubly linked list
 * @h: pointer to a node in the list
 *
 * Return: number of nodes in the list
 */

size_t printList(const stack_t *h)
{
	stack_t *seek, *head;
	size_t nodes;

	if (!h)/*check if list is NULL*/
		return (0);
	head = (stack_t *)h;
	while (head->prev) /*find the head*/
		head = head->prev;
	seek = head;
	for (nodes = 0; seek != NULL; nodes++)/*increment nodes until NULL*/
	{
		printf("%d\n", seek->n);/*print each integer*/
		seek = seek->next;
	}
	return (nodes);
}

/**
 * freeList - frees all nodes in a doubly linked list
 *
 * @head: pointer to the list
 */

void freeList(stack_t *head)
{
	stack_t *hide, *seek;

	if (!head)
		return;
	seek = head;
	while (seek->prev)/*find true head*/
		seek = seek->prev;
	while (seek)
	{
		hide = seek;
		seek = seek->next;
		free(hide);
	}
}

/**
 * new_tail - adds a node to the end of a doubly linked list
 * @head: pointer to the list
 * @n: integer value to store in the node
 *
 * Return: pointer to new node, NULL on failure
 */

stack_t *new_tail(stack_t **head, const int n)
{
	stack_t *new, *tail;

	new = malloc(sizeof(stack_t));
	if (!new)
	{
		dprintf(STDERR_FILENO, "Error: malloc failed");
		putchar('\n');
		opCommand[4] = "ERROR";
		return (NULL);
	}
	new->n = n;
	new->next = NULL;
	if (!*head)/*no current nodes*/
	{
		new->prev = NULL;
		*head = new;
	}
	else
	{
		tail = *head;
		while (tail->next)/*find the tail*/
			tail = tail->next;
		tail->next = new;
		new->prev = tail;
	}
	return (new);
}
