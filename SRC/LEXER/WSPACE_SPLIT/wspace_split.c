/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wspace_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 03:24:26 by senyilma          #+#    #+#             */
/*   Updated: 2023/10/21 08:14:22 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

static int	wspace(char *str)
{
	if (ft_strchr(str, 9))
		return (9);
	if (ft_strchr(str, 10))
		return (10);
	if (ft_strchr(str, 13))
		return (13);
	if (ft_strchr(str, 32))
		return (32);
	return (0);
}

t_list	*wspace_split(char **lex_flist)
{
	int		i;
	int		j;
	char	**space_split;
	t_list	*lex_slist = NULL;

	i = -1;
	while (lex_flist[++i])
	{
		if (!strchr_quotes(lex_flist[i]))
		{
			space_split = ft_split(lex_flist[i], wspace(lex_flist[i]));
			j = -1;
			while (space_split[++j])
			{
				ft_lstadd_back(&lex_slist, ft_lstnew(ft_strdup(space_split[j])));
				free(space_split[j]);
			}
		}
		else
			ft_lstadd_back(&lex_slist, ft_lstnew(ft_strdup(lex_flist[i])));
		free(lex_flist[i]);
	}
	free(space_split);
	free(lex_flist);
	return (lex_slist);
}
