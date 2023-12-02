/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_process.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 15:23:44 by senyilma          #+#    #+#             */
/*   Updated: 2023/12/02 20:15:06 by senyilma         ###   ########.fr       */
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
	//g_prime->exit_code = WEXITSTATUS(g_prime->exit_code);
	g_prime->exit_code = status;
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
