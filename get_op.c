#include "monty.h"

/**
 *
 */
void (*get_op(char *str))(stack_t **stack, unsigned int line_number)
{
	instruction_t ops[] = {
		{"push", push},
		{"pall", pall},
		{"pint", pint},
		{NULL, NULL}
	};
	unsigned int i = 0;

	while (ops[i].opcode && strcmp(str, ops[i].opcode) != 0)
		i++;

	return (ops[i].f);
}
