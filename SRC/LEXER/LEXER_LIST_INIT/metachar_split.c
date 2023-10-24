/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metachar_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 17:06:45 by senyilma          #+#    #+#             */
/*   Updated: 2023/10/24 09:20:03 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

int	chrchr_metachar(char c)
{
	if (c == PIPE)
		return (1);
	else if (c == SOR)
		return (2);
	else if (c == SIR)
		return (3);
	else
		return (0);
}

int	strchr_metachar(char *content)
{
	int	i;

	i = -1;
	while (content[++i])
	{
		if (chrchr_metachar(content[i]))
			return (1);
	}
	return (0);
}

void	metachar_split(char *content)
{
	int		end;
	int		start;
	char	*str;
	int		expand;

	end = 0;
	expand = 0;
	while (content[end])
	{
		start = end;
		if (chrchr_metachar(content[start]))
			while (content[end] == content[start])
				end++;
		else
			while (content[end] && !chrchr_metachar(content[end]))
				end++;
		str = ft_substr(content, start, end - start);
		if (ft_strchr(str, '$'))
			expand = 1;
		lexer_add_node(str, chrchr_metachar(*str), expand);
		free(str);
	}
}

void	create_nodes(t_list *lex_slist)
{
	t_list	*temp;
	int		expand;

	temp = lex_slist;
	while (temp)
	{
		expand = 0;
		if (strchr_quotes(temp->content) || !strchr_metachar(temp->content))
		{
			if ((*(char *)(temp->content) != S_QUOTES)
				&& ft_strchr(temp->content, '$'))
				expand = 1;
			lexer_add_node(temp->content, 0, expand);
		}
		else
			metachar_split(temp->content);
		lex_slist = temp;
		temp = temp->next;
		free(lex_slist);
	}
}
