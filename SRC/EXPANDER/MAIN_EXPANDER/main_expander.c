/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkati <mkati@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:29:10 by senyilma          #+#    #+#             */
/*   Updated: 2023/12/06 20:16:46 by mkati            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

static char	*expand_content(t_prime *g_prime, char *content, int *env)
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
				substr = d_quotes_expand(g_prime, content, &end, env);
			else
				substr = straight_expand(g_prime, content, &end, env);
			if (null_check_substr(substr, joinedstr))
				break ;
		}
		joinedstr = ft_strjoin(joinedstr, substr);
		free(substr);
	}
	return (joinedstr);
}

static char	*put_straight(char *content)
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
	int		env;

	env = 0;
	if (!g_prime->lexer)
		return ;
	temp = g_prime->lexer;
	while (temp)
	{
		if (!ownstrcmp(temp->content, "~"))
			expander_add_node(&g_prime->expander, ft_strdup(getenv("HOME")), \
				temp, env);
		if (!ft_strchr(temp->content, '$'))
			expander_add_node(&g_prime->expander, put_straight(temp->content), \
				temp, env);
		else
			expander_add_node(&g_prime->expander, \
				expand_content(g_prime, temp->content, &env), temp, env);
		temp = temp->next;
	}
}
