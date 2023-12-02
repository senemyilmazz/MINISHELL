/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_executer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 00:05:05 by senyilma          #+#    #+#             */
/*   Updated: 2023/12/02 19:08:56 by senyilma         ###   ########.fr       */
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
