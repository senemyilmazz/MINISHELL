/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metachar_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:04:38 by senyilma          #+#    #+#             */
/*   Updated: 2023/10/31 19:49:20 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

void	metachar_split2(char *content, t_list **lex_mlist)
{
	int		end;
	int		start;

	end = 0;
	while (content[end])
	{
		start = end;
		if (chrchr_metachar(content[start]))
			while (content[end] && content[end] == content[start])
				end++;
		else
		{
			while (content[end] && !chrchr_metachar(content[end]))
			{
				if (chrchr_quotes(content[start]))
					while (content[++end] && content[end] != content[start])
						;
				end++;
			}
		}
		ft_lstadd_back(lex_mlist, \
			ft_lstnew(ft_substr(content, start, end - start)));
	}
}

t_list	*metachar_split(t_list *lex_slist)
{
	t_list	*temp;
	t_list	*lex_mlist;

	lex_mlist = NULL;
	temp = lex_slist;
	while (temp)
	{
		if (!strchr_metachar(temp->content))
			ft_lstadd_back(&lex_mlist, ft_lstnew(temp->content));
		else
			metachar_split2(temp->content, &lex_mlist);
		lex_slist = temp;
		temp = temp->next;
		free(lex_slist);
	}
	return (lex_mlist);
}
