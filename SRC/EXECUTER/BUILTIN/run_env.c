/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkati <mkati@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 05:34:12 by senyilma          #+#    #+#             */
/*   Updated: 2023/12/06 18:59:33 by mkati            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

void	run_env(t_prime *g_prime, t_parser *parser)
{
	t_env_l	*temp_env;

	if (!search_path(g_prime->env_l, "PATH"))
		return ;
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
