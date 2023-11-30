/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 00:05:05 by senyilma          #+#    #+#             */
/*   Updated: 2023/11/30 18:02:13 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

void	executer(t_prime *g_prime)
{
	t_parser	*parser;

	if (!g_prime)
		return ;
	parser = g_prime->parser;
	while (parser)
	{
		pipe(g_prime->fd);
		run_command(g_prime, parser);
		parser = parser->next;
	}
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
	if (builtin_ret)
		run_builtin(g_prime, builtin_ret);
	else
		run_execve(g_prime, parser);
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

void	run_builtin(t_prime *g_prime, int built_type)
{
	//if (g_prime->cmd_count > 1);
		//dup_stdio(g_prime, g_prime->parser);
	if (built_type == ECHO)
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

void	run_execve(t_prime *g_prime, t_parser *parser)
{
	char	**env_list;
	char	*command;

	command = NULL;
	env_list = NULL;
	parser->pid = fork();
	if (parser->pid == 0)
	{
		env_list = get_env_cpy(g_prime);
		command = get_command(g_prime, parser);
		dup_stdio(g_prime, parser);
		tempfd_init(g_prime);
		execve(command, parser->parameters, env_list);
		if (parser->command)
			print_error(parser->command, " command not found!\n");
		free_prime(g_prime);
		exit(127);
	}
	fd_closer(g_prime);
	waitpid(parser->pid, NULL, 0);
	free(command);
	//free_env_cpy(env_list);
	g_prime->count++;
	g_prime->exit_code = WEXITSTATUS(g_prime->exit_code);
}
