#include "../../../INCLUDE/minishell.h"

void	dup_stdio(t_prime *g_prime, t_parser *parser)
{
	int	fd[2];

	tempfd_init(g_prime);
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

void	tempfd_init(t_prime *g_prime)
{
	if (g_prime->count != 0)
	{
		dup2(g_prime->exec_fd, STDIN_FILENO);
	}
	if (g_prime->count != g_prime->cmd_count - 1)
	{
		dup2(g_prime->fd[1], STDOUT_FILENO);
	}
	close(g_prime->fd[1]);
	close(g_prime->fd[0]);
}

void	fd_closer(t_prime *g_prime)
{
	g_prime->exec_fd = g_prime->fd[0];
	close(g_prime->fd[1]);
}
