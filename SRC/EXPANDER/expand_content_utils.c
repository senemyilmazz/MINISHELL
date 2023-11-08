/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_content_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:00:47 by senyilma          #+#    #+#             */
/*   Updated: 2023/11/07 18:35:30 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDE/minishell.h"

char	*straight_expand(t_prime *g_prime, char *content, int *end)
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
			substr = dollar_analysis(content, &i, g_prime);
			if (!substr)
			{
				*end = i;
				return (NULL);
			}
		}
		joinedstr = ft_strjoin(joinedstr, substr);
	}
	*end = i;
	return (joinedstr);
}

char	*d_quotes_expand(t_prime *g_prime, char *content, int *end)
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
			substr = dollar_analysis(content, &i, g_prime);
			if (!substr)
			{
				*end = i;
				if (content[i] != '\0')
					*end = i + 1;
				return (NULL);
			}
		}
		joinedstr = ft_strjoin(joinedstr, substr);
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
