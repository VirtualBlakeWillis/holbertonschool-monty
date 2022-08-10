#include "monty.h"

unsigned int isFail;
/**
 * main - monty main function
 *
 * @ac: # of args
 * @av: array of args
 * Return: 0 on success, 1 on failure
 */
int main(int ac, char **av)
{
	FILE *file_fd;

	isFail = 0;
	if (ac != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		return (EXIT_FAILURE);
	}

	file_fd = fopen(av[1], "r");
	if (file_fd == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", av[1]);
		return (EXIT_FAILURE);
	}

	if (read_file(file_fd) == EXIT_FAILURE)
	{
		/* failure */
		fclose(file_fd);
		return (EXIT_FAILURE);
	}
	fclose(file_fd);
	return (EXIT_SUCCESS);
}

/**
 * read_file - read a file
 *
 * @fd: FILE pointer
 * Return: 0 on success, 1 on failure
 */
int read_file(FILE *fd)
{
	stack_t *head = NULL;
	char *buff = NULL;
	size_t buffsize = 0;
	ssize_t nread;
	unsigned int lnum = 0;

	while ((nread = getline(&buff, &buffsize, fd)) != -1)
	{
		lnum++;
		/* fwrite(buff, nread, buffsize, stdout); */
		parse_line(buff, &head, lnum);
		if (isFail == 1)
		{
			if (buff != NULL)
				free(buff);
			buff = NULL;
			free_stack(head);
			return (EXIT_FAILURE);
		}
	}

	if (buff != NULL)
		free(buff);
	free_stack(head);
	return (EXIT_SUCCESS);
}

/**
 * parse_line - parse a line from getline
 *
 * @buff: output from getline
 * @head: head of stack
 * @lnum: line number
 * Return: 0 on success, 1 on failure
 */
int parse_line(char *buff, stack_t **head, unsigned int lnum)
{
	char *token;
	void (*f)(stack_t **stack, unsigned int line_number);
	unsigned int i = 0;

	token = strtok(buff, " \t\n");
	if (token == NULL)
	{
		return (EXIT_SUCCESS);
	}

	f = get_op(token);
	if (f == NULL)
	{
		fprintf(stderr, "unknown func: %s L%d\n", token, lnum);
		isFail = 1;
		return (EXIT_FAILURE);
	}
	f(head, lnum);

	if (strcmp(token, "push") == 0)
	{
		token = strtok(NULL, " \t\n");
		do {
			if (token && (isdigit(token[i]) || token[i] == '-'))
				i++;
			else
			{
				fprintf(stderr, "L%d: usage: push integer\n", lnum);
				isFail = 1;
				return (EXIT_FAILURE);
			}
		} while (token[i]);
		(*head)->n = atoi(token);
	}
	return (EXIT_SUCCESS);
}

/**
 * get_op - get opcode function
 *
 * @str: opcode command
 * Return: function pointer
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
	if (ops[i].opcode == NULL)
		return (NULL);
	return (ops[i].f);
}

/**
 * free_stack - frees a stack
 *
 * @head: head of a stack
 * Return: void
 */
void free_stack(stack_t *head)
{
	stack_t *temp = head;

	if (temp == NULL)
		return;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp);
	}
	free(head);
}
