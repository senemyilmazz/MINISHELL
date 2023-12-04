/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wspace_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 03:42:33 by senyilma          #+#    #+#             */
/*   Updated: 2023/12/01 00:37:53 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

t_list	*wspace_split(char *line, int start, int end, int quotes)
{
	t_list	*lex_slist;

	lex_slist = NULL;
	while (line && line[end])
	{
		start = end;
		if (chrchr_wspace(line[end]))
			while (line[end] && chrchr_wspace(line[end]))
				end++;
		else
		{
			while (line[end] && !chrchr_wspace(line[end]))
			{
				quotes = line[end];
				if (chrchr_quotes(line[end]))
					while (line[++end] && line[end] != quotes)
						;
				end++;
			}
			ft_lstadd_back(&lex_slist, ft_lstnew \
				(ft_substr(line, start, end - start)));
		}
	}
	return (lex_slist);
}
