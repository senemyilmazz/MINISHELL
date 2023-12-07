/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_process.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 15:23:44 by senyilma          #+#    #+#             */
/*   Updated: 2023/12/07 10:40:10 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

void	open_pipes(t_prime *g_prime)
{
	int			**fd;
	int			i;

	if (g_prime->cmd_count > 1)
	{
		fd = (int **)malloc(sizeof(int *) * (g_prime->cmd_count -1));
		i = -1;
		while (++i < g_prime->cmd_count -1)
			fd[i] = malloc(sizeof(int) * 2);
		g_prime->fd = fd;
		i = -1;
		while (++i < g_prime->cmd_count -1)
			pipe(g_prime->fd[i]);
	}
}

void	wait_all(t_prime *g_prime, int builtin)
{
	t_parser	*parser;
	int			status;

	parser = g_prime->parser;
	while (parser && builtin <= 1)
	{
		if (parser->command)
		{
			waitpid(parser->pid, &status, 0);
			if (status == (127 * 256))
				command_error(0, parser->command, \
					"command not found!", g_prime);
			if (status == 32766 && !chdir(parser->command))
				status = 32256;
			g_prime->exit_code = status / 256;
		}
		parser = parser->next;
	}
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
