/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:29:10 by senyilma          #+#    #+#             */
/*   Updated: 2023/11/10 17:26:49 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDE/minishell.h"

char	*expand_content(t_prime *g_prime, char *content)
{
	int		end;
	char	*joinedstr;
	char	*substr;

	joinedstr = 0;
	end = 0;
	while (content[end])
	{
		if (content[end] == S_QUOTES)
			substr = quotes_trim(content, &end, S_QUOTES);
		else
		{
			if (content[end] == D_QUOTES)
				substr = d_quotes_expand(g_prime, content, &end);
			else
				substr = straight_expand(g_prime, content, &end);
		}
		joinedstr = ft_strjoin(joinedstr, substr);
		free(substr);
	}
	return (joinedstr);
}

char	*put_straight(char *content)
{
	int		start;
	int		end;
	char	*substr;
	char	*joinedstr;

	end = 0;
	substr = NULL;
	joinedstr = NULL;
	while (content[end])
	{
		start = end;
		if (!chrchr_quotes(content[end]))
		{
			while (content[end] && !chrchr_quotes(content[end]))
				end++;
			substr = ft_substr(content, start, end - start);
		}
		else
			substr = quotes_trim(content, &end, content[end]);
		joinedstr = ft_strjoin(joinedstr, substr);
		free(substr);
	}
	return (joinedstr);
}

void	expander(t_prime *g_prime)
{
	t_lexer	*temp;

	if (!g_prime->lexer)
		return ;
	temp = g_prime->lexer;
	while (temp)
	{
		if (!ft_strchr(temp->content, '$'))
			expander_add_node(&g_prime->expander, put_straight(temp->content), \
				temp->type);
		else
			expander_add_node(&g_prime->expander, \
				expand_content(g_prime, temp->content), temp->type);
		temp = temp->next;
	}
}
