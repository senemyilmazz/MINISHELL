/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 23:42:26 by senyilma          #+#    #+#             */
/*   Updated: 2023/12/04 12:49:12 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

void	run_unset(t_prime *g_prime)
{
	char	**temp_name;
	int		array_len;

	g_prime->exit_code = 0;
	array_len = parameters_count(g_prime->parser->parameters);
	if (array_len > 1)
	{
		temp_name = g_prime->parser->parameters;
		while (*(++temp_name))
		{
			if (!env_arg_control(g_prime, *temp_name))
			{
				command_error(0, "unset", "not a valid identifier", g_prime);
				continue ;
			}
			else
				delete_env(g_prime, *temp_name);
		}
	}
}

void	delete_env(t_prime *g_prime, char *name)
{
	t_env_l	*env;
	t_env_l	*temp_env;

	env = g_prime->env_l;
	while (env)
	{
		if (!ownstrcmp(env->name, name))
		{
			if (env->content)
				free(env->content);
			free(env->name);
			if (g_prime->env_l == env)
				g_prime->env_l = g_prime->env_l->next;
			else
				temp_env->next = env->next;
			free(env);
			break ;
		}
		temp_env = env;
		env = env->next;
	}
}
