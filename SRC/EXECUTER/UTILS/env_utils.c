/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 09:00:41 by senyilma          #+#    #+#             */
/*   Updated: 2023/12/01 12:15:51 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

char	**get_env_cpy(t_prime *g_prime)
{
	char	**envlist;
	char	*temp_env;
	t_env_l	*temp_envlist;

	envlist = NULL;
	temp_envlist = g_prime->env_l;
	while (temp_envlist)
	{
		if (temp_envlist->content)
		{
			temp_env = NULL;
			temp_env = ft_strjoin(temp_env, temp_envlist->name);
			temp_env = ft_strjoin(temp_env, "=");
			temp_env = ft_strjoin(temp_env, temp_envlist->content);
			envlist = dynamic_malloc(envlist, temp_env);
		}
		temp_envlist = temp_envlist->next;
	}
	return (envlist);
}

void	free_env_cpy(char **envlist)
{
	char	**temp;

	temp = envlist;
	while (*envlist)
		free(*(envlist++));
	free(temp);
	temp = NULL;
}

char	*get_oldpwd(t_env_l *env, char *path)
{
	t_env_l	*temp_env;

	temp_env = env;
	while (temp_env)
	{
		if (!ownstrcmp(temp_env->name, path))
			return (temp_env->content);
		temp_env = temp_env->next;
	}
	return (NULL);
}