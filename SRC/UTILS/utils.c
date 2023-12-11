/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 00:24:33 by senyilma          #+#    #+#             */
/*   Updated: 2023/12/11 00:24:35 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDE/minishell.h"

char	**dynamic_malloc(char **path, char *new)
{
	int		count;
	char	**new_path;
	int		i;

	count = 0;
	while (path && path[count])
		count++;
	new_path = (char **)malloc(sizeof(char *) * (count + 2));
	if (!new_path)
		return (NULL);
	i = -1;
	while (++i < count)
		new_path[i] = ft_strdup(path[i]);
	new_path[i] = ft_strdup(new);
	new_path[++i] = NULL;
	i = -1;
	if (path)
	{
		while (path[++i])
			free(path[i]);
		free(path);
	}
	return (new_path);
}

int	ownstrcmp(char *s1, char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (1);
	i = -1;
	while (s1[++i])
	{
		if (s1[i] != s2[i])
			break ;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	parameters_count(char **str)
{
	int	count;

	count = 0;
	while (str && *(str++))
		count++;
	return (count);
}

void	double_str_free(char **str)
{
	int	i;

	i = -1;
	while (str && str[++i])
		free(str[i]);
	if (str)
		free(str);
}

void	*free_null(void *str)
{
	if (str)
		free(str);
	return (0);
}
