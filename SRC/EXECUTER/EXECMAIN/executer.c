/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 00:05:05 by senyilma          #+#    #+#             */
/*   Updated: 2023/11/29 13:47:31 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

void	executer(t_prime *g_prime)
{
	int			fd[2];
	t_parser	*parser;

	if (!g_prime)
		return ;
	parser = g_prime->parser;
	while (parser)
	{
		if (g_prime->cmd_count > 1)
			pipe(fd);
		run_command(g_prime, parser, fd);
		//if (fd[0] && fd[1])
		//{
		//	close(fd[0]);
		//	close(fd[1]);
		//	fd[0] = 0;
		//	fd[1] = 0;
		//}
		parser = parser->next;
	}
}

void	run_command(t_prime *g_prime, t_parser *parser, int *fd)
{
	char	*cmd;
	int		builtin_ret;

	builtin_ret = 0;
	if (parser->command)
	{
		cmd = check_cmd(parser->command);
		builtin_ret = is_builtin(cmd);
	}
	if (builtin_ret)
		run_builtin(g_prime, builtin_ret, fd);
	else
		run_execve(g_prime, parser, fd);
}

int	is_builtin(char *str)
{
	if (!str)
		return (1);
	else if (!ownstrcmp(str, "echo") || !ownstrcmp(str, "ECHO"))
		return (ECHO);
	else if (!ownstrcmp(str, "cd"))
		return (CD);
	else if (!ownstrcmp(str, "pwd") || !ownstrcmp(str, "PWD"))
		return (PWD);
	else if (!ownstrcmp(str, "export"))
		return (EXPORT);
	else if (!ownstrcmp(str, "unset"))
		return (UNSET);
	else if (!ownstrcmp(str, "env") || !ownstrcmp(str, "ENV"))
		return (ENV);
	else if (!ownstrcmp(str, "exit"))
		return (EXIT);
	else
		return (0);
}

void	run_builtin(t_prime *g_prime, int built_type, int *fd)
{
	if (g_prime->cmd_count > 1)
		dup_stdio(g_prime, g_prime->parser, fd);
	else if (built_type == ECHO)
		run_echo(g_prime);
	else if (built_type == CD)
		run_cd(g_prime);
	else if (built_type == PWD)
		run_pwd(g_prime);
	else if (built_type == EXPORT)
		run_export(g_prime);
	else if (built_type == UNSET)
		run_unset(g_prime);
	else if (built_type == ENV)
		run_env(g_prime);
	else if (built_type == EXIT)
		run_exit(g_prime);
}

void	run_execve(t_prime *g_prime, t_parser *parser, int *fd)
{
	char	**env_list;
	char	*command;

	command = NULL;
	parser->pid = fork();
	if (parser->pid == 0)
	{
		env_list = get_env_cpy(g_prime);
		command = get_command(g_prime, parser);
		dup_stdio(g_prime, parser, fd);
		execve(command, parser->parameters, env_list);
		if (parser->command)
			print_error(parser->command, " command not found!\n");
		free_env_cpy(env_list);
		free_prime(g_prime);
		free(command);
		exit(127);
	}
	free(command);
	waitpid(parser->pid, &g_prime->exit_code, 0);
	g_prime->exit_code = WEXITSTATUS(g_prime->exit_code);
}

void	dup_stdio(t_prime *g_prime, t_parser *parser, int *fd)
{
	int	new_fd[2];

	if (parser->infile == -2)
	{
		pipe(new_fd);
		write(new_fd[1], g_prime->parser->heredoc, \
			ft_strlen(g_prime->parser->heredoc));
		close (new_fd[1]);
		dup2(new_fd[0], STDOUT_FILENO);
		close(new_fd[0]);
	}
	if (parser->infile > 2)
		dup2(parser->infile, STDIN_FILENO);
	else if (g_prime->cmd_count > 1 && parser != g_prime->parser)
	{
		close (new_fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close (new_fd[0]);
	}
	if (parser->outfile > 2)
	{
		dup2(parser->outfile, STDOUT_FILENO);
	}
	else if (g_prime->cmd_count > 1 && parser->next)
	{
		close (new_fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close (new_fd[1]);
	}
}
