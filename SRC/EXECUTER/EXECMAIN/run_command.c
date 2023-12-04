/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 15:21:41 by senyilma          #+#    #+#             */
/*   Updated: 2023/12/04 20:11:50 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

void	run_execve(t_prime *g_prime, t_parser *parser, int i)
{
	char	**env_list;
	char	*command;

	command = NULL;
	env_list = NULL;
	if (!stat_check(g_prime, parser->command) || parser->infile == 2)
		exit (1);
	env_list = get_env_cpy(g_prime);
	command = get_command(g_prime, parser);
	dup_stdio(g_prime, parser, i);
	execve(command, parser->parameters, env_list);
	exit(127);
}

void	run_builtin(t_prime *g_prime, t_parser *parser, int built_type, int i)
{
	(void)i;
	dup_stdio(g_prime, parser, 0);
	if (built_type == EKKO)
		run_echo(g_prime, parser);
	else if (built_type == CD)
		run_cd(g_prime);
	else if (built_type == PWD)
		run_pwd(g_prime, parser);
	else if (built_type == EXPORT)
		run_export(g_prime, parser);
	else if (built_type == UNSET)
		run_unset(g_prime);
	else if (built_type == ENV)
		run_env(g_prime, parser);
	else if (built_type == EXIT)
		run_exit(g_prime, parser);
}
