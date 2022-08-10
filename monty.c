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
 * read_file - 
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
			return (EXIT_FAILURE);
		}
	}

	if (buff != NULL)
		free(buff);
	
	return (EXIT_SUCCESS);
}

/**
 *
 */
int parse_line(char *buff, stack_t **head, unsigned int lnum)
{
	char *token;
	void (*f)(stack_t **stack, unsigned int line_number);
	
	token = strtok(buff, " \t");
	f = get_op(token);
	
	f(head, lnum);

	if (strcmp(token, "push") == 0)
	{
		token = strtok(NULL, " \t\n");
		if (strcmp(token,"0") == 0)
			(*head)->n = 0;
		if (token == NULL)
		{
			fprintf(stderr, "L%d: usage: push integer\n", lnum);
			isFail = 1;
			return (EXIT_FAILURE);
		}
		else
		{
			(*head)->n = atoi(token);
			if ((*head)->n == 0)
			{
				fprintf(stderr, "L%d: usage: push integer\n", lnum);
				isFail = 1;
				return (EXIT_FAILURE);
			}
		}
	}
	return (EXIT_SUCCESS);
}
