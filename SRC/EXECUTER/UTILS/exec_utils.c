/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 00:25:21 by senyilma          #+#    #+#             */
/*   Updated: 2023/12/11 00:25:23 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

int	update_env(t_prime *g_prime, char *env_name, char *new_arg)
{
	t_env_l	*env;
	char	*temp_str;

	env = g_prime->env_l;
	temp_str = NULL;
	while (env)
	{
		if (!ownstrcmp(env->name, env_name))
		{
			if (env->content)
				free(env->content);
			env->content = NULL;
			if (!new_arg)
				return (1);
			env->content = ft_strjoin(env->content, new_arg);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

char	*get_env_name(char *content)
{
	char	*name;
	int		i;

	i = 0;
	while (content[i] && content[i] != '=')
		i++;
	name = ft_substr(content, 0, i);
	return (name);
}

void	add_newenv(t_prime *g_prime, char *env)
{
	char	*content;
	char	*name;

	name = get_env_name(env);
	content = env + ft_strlen(name);
	if (*content == '=' && *(content + 1))
		content = ft_strdup(content + 1);
	else
		content = NULL;
	env_lstadd_back(&g_prime->env_l, env_listnew(name, content));
}
