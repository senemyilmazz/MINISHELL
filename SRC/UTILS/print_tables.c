#include "../../INCLUDE/minishell.h"


void	print_lexer(t_prime	*g_prime)
{
	t_lexer	*temp;

	temp = g_prime->lexer;
	printf("\n-----------{ LEXER }-----------\n");
	while (temp)
	{
		printf("C:%s\nT:%d\n", temp->content, temp->type);
		printf("-------------------------------\n");
		temp = temp->next;
	}
	printf("\n\n");
}


void	print_parser(t_prime *g_prime)
{
	t_parser	*temp;
	int			i;

	if (!g_prime->parser)
		return ;
	temp = g_prime->parser;
	printf("\n-----------{ PARSER }----------\n");
	while (temp)
	{
		printf("command: %s\n", temp->command);
		printf("args: ");
		i = -1;
		while (temp->parameters && temp->parameters[++i])
			printf(" %s ; ", temp->parameters[i]);
		printf("\ninfile: %d\n", temp->infile);
		printf("outfile: %d\n", temp->outfile);
		while (temp->file)
		{
			printf("{filename: %s ; re_type %d}", \
				temp->file->filename, temp->file->re_type);
			temp->file = temp->file->next;
		}
		if (temp->heredoc)
			printf("\nheredoc: %s", temp->heredoc);
		printf("\n-------------------------------\n");
		temp = temp->next;
	}
}

void	print_expander(t_prime	*g_prime)
{
	t_expander	*temp;

	temp = g_prime->expander;
	printf("\n---------{ EXPANDER }----------\n");
	while (temp)
	{
		printf("C:%s\nT:%d\n", temp->content, temp->type);
		printf("env:%d\n", temp->env);
		if (temp->ex_content)
			printf("ex_cont:%s\n", temp->ex_content);
		printf("-------------------------------\n");
		temp = temp->next;
	}
	printf("\n\n");
}
