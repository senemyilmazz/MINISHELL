#include "../../../INCLUDE/minishell.h"

void	dup_stdio(t_prime *g_prime, t_parser *parser)
{
	int	fd[2];

	if (parser->infile == -2)
	{
		pipe(fd);
		write(fd[1], g_prime->parser->heredoc, \
			ft_strlen(g_prime->parser->heredoc));      		// HEREDOC DÜZENLENECEK VE REDİREÇTİYON DÜZENLENECEK!!!
		close (fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	if (g_prime->parser->outfile > 2)
		dup2(g_prime->parser->outfile, STDOUT_FILENO);
	if (g_prime->parser->infile > 2)
		dup2(g_prime->parser->infile, STDIN_FILENO);
}

void	tempfd_init(t_prime *g_prime)
{
	if (g_prime->count != 0)
	{
		dup2(g_prime->exec_fd, 0);
		close(g_prime->exec_fd);
	}
	if (g_prime->count != g_prime->cmd_count - 1)
	{
		dup2(g_prime->fd[1], 1);
		close(g_prime->exec_fd);
	}
	close(g_prime->fd[1]);
	close(g_prime->fd[0]);
}

void	fd_closer(t_prime *g_prime)
{
	if (g_prime->count != 0)
		close(g_prime->exec_fd);
	close(g_prime->fd[1]);
	g_prime->exec_fd = g_prime->fd[0];
}