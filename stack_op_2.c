#include "monty.h"

/**
 * add - add top 2 nodes of stack
 *
 * @h: head of stack
 * @ln: line number
 * Return: void
 */
void add(stack_t **h, unsigned int ln)
{
	unsigned int sum;
	stack_t *temp = (*h)->next;

	if (!temp)
	{
		fprintf(stderr, "L%d: can't add, stack too short\n", ln);
	}
	sum = (*h)->n + temp->n;
	temp->n = sum;
	pop(h, ln);
}

/**
 * nop - do nothing
 *
 * @h: haed of stack
 * @ln: line number
 * Return: void
 */
void nop(stack_t **h, unsigned int ln)
{
	(void)h;
	(void)ln;
}
