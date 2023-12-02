/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 09:00:41 by senyilma          #+#    #+#             */
/*   Updated: 2023/12/02 16:04:01 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

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