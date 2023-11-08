/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 19:30:44 by senyilma          #+#    #+#             */
/*   Updated: 2023/11/07 21:17:27 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDE/minishell.h"

char	**dynamic_malloc(char **path, char *new)
{
	int		count;
	char	**new_path;
	int		i;

	count = 0;
	if (path)
	{
		while (path[count])
			count++;
	}
	new_path = (char **)malloc(sizeof(char *) * (count + 2));
	if (!new_path)
		return (NULL);
	i = 0;
	if (path)
	{
		while (i < count)
		{
			new_path[i] = ft_strdup(path[i]);
			i++;
		}
	}
	new_path[i] = ft_strdup(new);
	new_path[++i] = NULL;
	i = -1;
	if (path)
	{
		while (path[++i])
			free(path[i]);
	}
	if (path)
		free(path);
	return (new_path);
}

