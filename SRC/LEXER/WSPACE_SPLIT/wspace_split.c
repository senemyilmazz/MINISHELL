/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wspace_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 03:24:26 by senyilma          #+#    #+#             */
/*   Updated: 2023/10/24 01:01:40 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

static int	chrchr_wspace(char c)
{
	return (c == 9 || c == 10 || c == 13 || c == 32);
}

static int	strchr_wspace(char *str)
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

static void	w_space_split2(char *str, t_list **lex_slist)
{
	int	end;
	int	start;

	end = 0;
	while (str[end])
	{
		start = end;
		if (chrchr_wspace(str[start]))
		{
			while (str[end] && chrchr_wspace(str[end]))
				end++;
		}
		else
		{
			while (str[end] && !chrchr_wspace(str[end]))
				end++;
			ft_lstadd_back(lex_slist, ft_lstnew \
				(ft_substr(str, start, end - start)));
		}
	}
}

t_list	*wspace_split(char **lex_flist)
{
	int		i;
	t_list	*lex_slist;

	lex_slist = NULL;
	i = -1;
	while (lex_flist[++i])
	{
		if (!strchr_quotes(lex_flist[i]) && strchr_wspace(lex_flist[i]))
			w_space_split2(lex_flist[i], &lex_slist);
		else
			ft_lstadd_back(&lex_slist, ft_lstnew(ft_strdup(lex_flist[i])));
		free(lex_flist[i]);
	}
	free(lex_flist);
	return (lex_slist);
}
