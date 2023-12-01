#include "../../../INCLUDE/minishell.h"

static void	tempfd_init(t_prime *g_prime, t_parser *parser)
{
	if (parser->next)
	{
		close(g_prime->fd[0]);
		dup2(g_prime->fd[1], STDOUT_FILENO);
		close(g_prime->fd[1]);
	}
	if (g_prime->parser != parser)
	{
		close(g_prime->fd[1]);
		dup2(g_prime->fd[0], STDIN_FILENO);
		close(g_prime->fd[0]);
	}
}

void	dup_stdio(t_prime *g_prime, t_parser *parser)
{
	int	fd[2];

	tempfd_init(g_prime, parser);
	if (parser->infile == -2)
	{
		pipe(fd);
		write(fd[1], parser->heredoc, ft_strlen(parser->heredoc));
		close (fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	if (parser->outfile > 2)
		dup2(parser->outfile, STDOUT_FILENO);
	if (parser->infile > 2)
		dup2(parser->infile, STDIN_FILENO);
}

void	fd_closer(t_prime *g_prime)
{
	close(g_prime->fd[1]);
	close(g_prime->fd[0]);
}
