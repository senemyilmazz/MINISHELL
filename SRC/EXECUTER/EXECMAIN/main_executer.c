/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_executer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 00:05:05 by senyilma          #+#    #+#             */
/*   Updated: 2023/12/04 21:36:54 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

void	executer(t_prime *g_prime)
{
	t_parser	*parser;
	int			i;
	int			builtin;

	if (!g_prime->parser)
		return ;
	open_pipes(g_prime);
	i = 0;
	parser = g_prime->parser;
	while (parser)
	{
		builtin = check_builtin(g_prime, parser);
		if (builtin > 1 && (builtin == EXIT || g_prime->cmd_count == 1))
			run_builtin(g_prime, parser, builtin, i);
		else if (builtin >= 0 && (parser->command && *parser->command))
		{
			parser->pid = fork();
			if (!parser->pid)
				run_execve(g_prime, parser, i);
		}
		i++;
		parser = parser->next;
	}
	fd_closer(g_prime);
	wait_all(g_prime, builtin);
}
