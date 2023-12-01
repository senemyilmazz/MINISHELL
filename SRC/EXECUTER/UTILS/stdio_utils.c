#include "../../../INCLUDE/minishell.h"

static void	tempfd_init(t_prime *g_prime, t_parser *parser, int i)
{
	if (g_prime->parser == parser)
	{
		dup2(g_prime->fd[i][1], STDOUT_FILENO);
	}
	else if (!parser->next)
	{
		dup2(g_prime->fd[i - 1][0], STDIN_FILENO);
	}
	else
	{
		dup2(g_prime->fd[i - 1][0], STDIN_FILENO);
		dup2(g_prime->fd[i][1], STDOUT_FILENO);
	}
	fd_closer(g_prime);
}


void	dup_stdio(t_prime *g_prime, t_parser *parser, int i)
{
	int	fd[2];

	if (g_prime->cmd_count > 1)
		tempfd_init(g_prime, parser, i);
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
	int	i;

	i = -1;
	while (++i < g_prime->cmd_count -1)
	{
		if (g_prime->fd[i][1])
			close(g_prime->fd[i][1]);
		if (g_prime->fd[i][0])
			close(g_prime->fd[i][0]);
	}
}

void	open_pipes(t_prime *g_prime)
{
	int			**fd;
	int			i;

	if (g_prime->cmd_count > 1)
	{
		fd = (int **)malloc(sizeof(int *) * (g_prime->cmd_count -1));
		i = -1;
		while (++i <  g_prime->cmd_count -1)
			fd[i] = malloc(sizeof(int) * 2);
		g_prime->fd = fd;
		i = -1;
		while (++i < g_prime->cmd_count -1)
			pipe(g_prime->fd[i]);
	}
}
