/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 19:30:44 by senyilma          #+#    #+#             */
/*   Updated: 2023/12/01 06:38:34 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

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

char	*pars_strjoin(char *s1, char *s2)
{
	char	*s1s2;
	size_t	i;
	size_t	j;

	s1s2 = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 2) * sizeof(char));
	if (!s1s2)
	{
		free (s1);
		return (NULL);
	}
	i = -1;
	while (++i < ft_strlen(s1))
		s1s2[i] = s1[i];
	j = -1;
	while (++j < ft_strlen(s2))
		s1s2[i + j] = s2[j];
	s1s2[i + j] = '\n';
	s1s2[i + j + 1] = '\0';
	if (s1)
		free(s1);
	return (s1s2);
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
