#include "monty.h"

/* create list, populate with nodes, delete nodes, free list */

/**
 * add_stack_node - add a node onto stack
 *
 * @h: head of stack
 * @n: data for node
 * Return: address of head, or NULL
 */
void push(stack_t **h, __attribute((unused))unsigned int ln)
{
	stack_t *new;

	new = malloc(sizeof(stack_t));
	if (new == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(37);
	}
	
	new->prev = NULL;

	if (*h == NULL)
	{
		new->next = NULL;
	}
	else
	{
		(*h)->prev = new;
		new->next = *h;
	}
	*h = new;
}

void pall(stack_t **h, __attribute__((unused))unsigned int ln)
{
	stack_t *temp = *h;
	while (temp)
	{
		printf("%d\n", temp->n);
		temp = temp->next;
	}
}

void pint(stack_t **h, unsigned int ln)
{
	if (*h == NULL)
	{
		fprintf(stderr, "L%d: can't pint, stack empty\n", ln);
		isFail = 1;
		return;
	}
	printf("%d\n", (*h)->n);
}
