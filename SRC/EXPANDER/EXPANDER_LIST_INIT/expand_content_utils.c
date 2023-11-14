/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_content_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:00:47 by senyilma          #+#    #+#             */
/*   Updated: 2023/11/15 01:20:40 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

char	*straight_expand(t_prime *g_prime, char *content, int *end, int *env)
{
	int		i;
	int		start;
	char	*joinedstr;
	char	*substr;

	joinedstr = NULL;
	i = *end;
	while (content[i] && !chrchr_quotes(content[i]))
	{
		start = i;
		if (content[i] != '$')
		{
			while (content[i] && content[i] != '$'
				&& content[i] != S_QUOTES && content[i] != D_QUOTES)
				i++;
			substr = ft_substr(content, start, i - start);
		}
		else
		{
			substr = dollar_analysis(content, &i, g_prime, env);
			if (!*substr && !*end && content[*end] == '$' && !content[i])
				*env = -1;
			if (!substr)
			{
				*end = i;
				return (NULL);
			}
		}
		joinedstr = ft_strjoin(joinedstr, substr);
		free(substr);
	}
	*end = i;
	return (joinedstr);
}

char	*d_quotes_expand(t_prime *g_prime, char *content, int *end, int *env)
{
	int		start;
	int		i;
	char	*substr;
	char	*joinedstr;

	joinedstr = NULL;
	i = *end + 1;
	while (content[i] && content[i] != D_QUOTES)
	{
		start = i;
		if (content[i] != '$')
		{
			while (content[i] && content[i] != '$' && content[i] != D_QUOTES)
				i++;
			substr = ft_substr(content, start, i - start);
		}
		else
		{
			substr = dollar_analysis(content, &i, g_prime, env);
			if (!substr)
			{
				*end = i;
				if (content[i] != '\0')
					*end = i + 1;
				return (NULL);
			}
		}
		joinedstr = ft_strjoin(joinedstr, substr);
		free(substr);
	}
	*end = i;
	if (content[i] != '\0')
		*end = i + 1;
	return (joinedstr);
}

char	*quotes_trim(char *content, int *end, char quotes)
{
	int		i;
	int		start;
	char	*substr;

	i = *end + 1;
	start = i;
	while (content[i] && content[i] != quotes)
		i++;
	substr = ft_substr(content, start, i - start);
	*end = i + 1;
	return (substr);
}
