/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 00:05:05 by senyilma          #+#    #+#             */
/*   Updated: 2023/12/01 20:23:52 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

void	executer(t_prime *g_prime)
{
	t_parser	*parser;
	int			i;

	if (!g_prime->parser)
		return ;
	open_pipes(g_prime);
	i = 0;
	parser = g_prime->parser;
	while (parser)
	{
		parser->pid = fork();
		if (parser->pid == 0)
		{
			dup_stdio(g_prime, parser, i);
			run_command(g_prime, parser);
		}
		parser = parser->next;
		i++;
	}
	parser = g_prime->parser;
	fd_closer(g_prime);
	wait_all(g_prime);
}

void	run_command(t_prime *g_prime, t_parser *parser)
{
	char	*cmd;
	int		builtin_ret;

	builtin_ret = 0;
	if (parser->command)
	{
		cmd = check_cmd(parser->command);
		builtin_ret = is_builtin(cmd);
	}
	if (builtin_ret && (builtin_ret == EXIT || g_prime->cmd_count == 1))
		run_builtin(g_prime, parser, builtin_ret);
	else
		run_execve(g_prime, parser);
}

void	run_builtin(t_prime *g_prime, t_parser *parser, int built_type)
{
	if (built_type == ECHO)
		run_echo(parser);
	else if (built_type == CD)
		run_cd(g_prime);
	else if (built_type == PWD)
		run_pwd(parser);
	else if (built_type == EXPORT)
		run_export(g_prime, parser);
	else if (built_type == UNSET)
		run_unset(g_prime);
	else if (built_type == ENV)
		run_env(g_prime, parser);
	else if (built_type == EXIT)
		run_exit(g_prime);
}

void	run_execve(t_prime *g_prime, t_parser *parser)
{
	char	**env_list;
	char	*command;

	command = NULL;
	env_list = NULL;
	if (parser->pid == 0)
	{
		env_list = get_env_cpy(g_prime);
		command = get_command(g_prime, parser);
		execve(command, parser->parameters, env_list);
		if (parser->command)
			print_error(parser->command, " command not found!\n");
		exit(127);
	}
	free(command);
	// free_env_cpy(env_list);
}


void	wait_all(t_prime *g_prime)
{
	t_parser	*parser;
	int			status;

	parser = g_prime->parser;
	while (parser)
	{
		waitpid(parser->pid, &status, 0);
		g_prime->exit_code = status;
		if (status == 127)
		{
			while (parser)
			{
				kill(parser->pid, SIGTERM);
				parser = parser->next;
			}
			break ;
		}
		parser = parser->next;
	}
	g_prime->exit_code = WEXITSTATUS(g_prime->exit_code);
}
