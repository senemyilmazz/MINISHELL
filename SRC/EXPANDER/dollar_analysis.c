/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:02:31 by senyilma          #+#    #+#             */
/*   Updated: 2023/11/07 18:15:00 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDE/minishell.h"

char	*check_env(t_prime *g_prime, char *substr)
{
	t_env_l	*iter;
	char	*str;

	iter = g_prime->env_l;
	str = NULL;
	while (iter)
	{
		if (!ft_strncmp(iter->name, substr, ft_strlen(substr)))
		{
			str = ft_strdup(iter->content);
			break ;
		}
		else
			str = ft_strdup("");
		iter = iter->next;
	}
	free (substr);
	return (str);
}

char	*dollar_expand(char *content, int *end, t_prime *g_prime)
{
	char	*substr;
	int		start;
	int		i;

	i = *end;
	start = i;
	while (content[i] && (ft_isalpha(content[i])
			|| ft_isdigit(content[i]) || content[i] == '_'))
		i++;
	substr = ft_substr(content, start, i - start);
	substr = check_env(g_prime, substr);
	*end = i - 1;
	return (substr);
}

char	*special_expand(char c, t_prime *g_prime)
{
	char	*substr;

	substr = NULL;
	if (c == '0')
		substr = ft_substr("minishell", 0, 9);
	if (c == '?')
		substr = ft_itoa(g_prime->exit_code);
	return (substr);
}

char	*dollar_analysis(char *content, int *end, t_prime *g_prime)
{
	int		i;
	int		start;
	char	*substr;

	i = *end;
	start = i + 1;
	if (ret_null(content[++i]))
		return (ft_strdup(""));
	else if (put_directly(content[i]))
		substr = ft_substr(content, start - 1, i - start + 2);
	else if (put_synerror(content[i]))
		return (NULL);
	else if (special_chars(content[i]))
		substr = special_expand(content[i], g_prime);
	else if (content[i] == '$')
		return (ft_strdup("$"));
	else if (chrchr_quotes(content[i]))
		substr = quotes_trim(content, &i, content[i]);
	else
		substr = dollar_expand(content, &i, g_prime);
	*end = i + 1;
	return (substr);
}
