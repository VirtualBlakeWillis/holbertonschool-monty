#ifndef MONTY_H
#define MONTY_H
/* structures */
/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;
/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

/* standard libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ctype.h>

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

unsigned int isFail;
/* function prototypes */
int read_file(FILE *fd);
int parse_line(char *line, stack_t **h, unsigned int lnum);

void push(stack_t **h, unsigned int ln);
void pall(stack_t **h, unsigned int ln);
void pint (stack_t **h, unsigned int ln);


void (*get_op(char *str))(stack_t **stack, unsigned int line_number);
#endif
