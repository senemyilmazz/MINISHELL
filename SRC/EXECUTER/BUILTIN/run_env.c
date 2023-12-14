/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 00:19:47 by senyilma          #+#    #+#             */
/*   Updated: 2023/12/11 14:55:37 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

void	run_env(t_prime *g_prime, t_parser *parser)
{
	t_env_l	*temp_env;

	if (!search_path(g_prime->env_l, "PATH"))
	{
		command_error(0, "env", "No such file or directory", g_prime);
		g_prime->exit_code = 127;
		return ;
	}
	temp_env = g_prime->env_l;
	while (temp_env)
	{
		if (temp_env->content)
		{
			write(parser->outfile, temp_env->name,
				ft_strlen(temp_env->name));
			write(parser->outfile, "=", 1);
			write(parser->outfile, temp_env->content,
				ft_strlen(temp_env->content));
			write(parser->outfile, "\n", 1);
		}
		temp_env = temp_env->next;
	}
	g_prime->exit_code = 0;
}
