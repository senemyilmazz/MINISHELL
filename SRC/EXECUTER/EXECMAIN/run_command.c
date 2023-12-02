/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 15:21:41 by senyilma          #+#    #+#             */
/*   Updated: 2023/12/02 19:04:52 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

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
	double_str_free(env_list);
}

void	run_builtin(t_prime *g_prime, t_parser *parser, int built_type)
{
	if (built_type == EKKO)
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
	exit(1); // değişiklik var ******************
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
		if (cmd)
			free(cmd);
	}
	if (builtin_ret && (builtin_ret == EXIT || g_prime->cmd_count == 1))
		run_builtin(g_prime, parser, builtin_ret);
	else
		run_execve(g_prime, parser);
}
