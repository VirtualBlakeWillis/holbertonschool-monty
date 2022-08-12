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
	stack_t *temp;

	if (*h == NULL || (*h)->next == NULL)
	{
		fprintf(stderr, "L%d: can't add, stack too short\n", ln);
		isFail = 1;
		return;
	}

	temp = (*h)->next;
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
