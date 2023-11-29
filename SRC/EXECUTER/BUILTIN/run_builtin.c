#include "../../../INCLUDE/minishell.h"

void	create_dup(t_prime *g_prime, t_parser *parser, int *fd, int fd_index)
{
	int	new_fd[2];

	if (g_prime->parser->infile == -2)
	{
		pipe(new_fd);
		write(new_fd[1], g_prime->parser->heredoc, \
			ft_strlen(g_prime->parser->heredoc));
		dup2(new_fd[1], STDOUT_FILENO);
		close (new_fd[1]);
		close(new_fd[0]);
	}
	if (g_prime->parser->infile > 2)
		dup2(g_prime->parser->infile, STDIN_FILENO);
	else if (fd && parser != g_prime->parser)    // fd != 0  && ilk node değilse
		dup2(fd[fd_index - 2], STDIN_FILENO);
	if (g_prime->parser->outfile > 2)
		dup2(g_prime->parser->outfile, STDOUT_FILENO);
	else if (fd && g_prime->parser->next)       // fd != 0 && son node değilse
		dup2(fd[fd_index + 1], STDOUT_FILENO);
	//if (fd_index >= 0)
	//	clear_pipe(fd);
}

void	run_builtin(t_prime *g_prime, int cmd_type, int *fd, int fd_index)
{
	if (fd)
		create_dup(g_prime, g_prime->parser, fd, fd_index);  //single command girmez!!
	else if (cmd_type == ECHO)
		run_echo(g_prime);
	else if (cmd_type == CD)
		run_cd(g_prime);
	else if (cmd_type == PWD)
		run_pwd(g_prime);
	else if (cmd_type == EXPORT)
		run_export(g_prime);
	else if (cmd_type == UNSET)
		run_unset(g_prime);
	else if (cmd_type == ENV)
		run_env(g_prime);
	else if (cmd_type == EXIT)
		run_exit(g_prime);
}
