/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 19:48:42 by senyilma          #+#    #+#             */
/*   Updated: 2023/10/23 20:16:44 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"

t_env_l	*env_listnew(char *name, char *content)
{
	t_env_l	*new;

	new = (t_env_l *)malloc(sizeof(t_env_l));
	if (!new)
		return (0);
	new->name = name;
	new->content = content;
	new->next = 0;
	return (new);
}

t_env_l	*env_lstlast(t_env_l	*lst)
{
	t_env_l	*temp;

	if (!lst)
		return (0);
	temp = lst;
	while (temp->next != 0)
	{
		temp = temp->next;
	}
	return (temp);
}

void	env_lstadd_back(t_env_l	**lst, t_env_l	*new)
{
	if (new)
	{
		if (!(*lst))
		{
			*lst = new;
			return ;
		}
		env_lstlast(*lst)->next = new;
		new->next = 0;
	}
}

void	init_env(char **env)
{
	int		i;
	int		start;
	int		end;
	char	*name;
	char	*content;

	i = -1;
	while (env[++i])
	{
		end = 0;
		while (env[i][end])
		{
			start = end;
			while (env[i][end] && env[i][end] != '=')
				end++;
			name = ft_substr(env[i], start, end);
			end++;
			start = end;
			while (env[i][end])
				end++;
			content = ft_substr(env[i], start, end);
			env_lstadd_back(&g_prime.env_l, env_listnew(name, content));
		}
	}
}
