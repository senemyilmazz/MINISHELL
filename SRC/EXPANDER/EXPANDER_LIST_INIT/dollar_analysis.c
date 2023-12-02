/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:02:31 by senyilma          #+#    #+#             */
/*   Updated: 2023/12/02 16:30:01 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

static char	*check_env(t_prime *g_prime, char *substr, int	*env)
{
	t_env_l	*iter;
	char	*str;

	iter = g_prime->env_l;
	str = NULL;
	while (iter)
	{
		if (!ownstrcmp(iter->name, substr))
		{
			str = ft_strdup(iter->content);
			*env = 1;
			break ;
		}
		iter = iter->next;
	}
	if (*env != 1)
		str = ft_strdup("");
	free (substr);
	return (str);
}

static char	*dollar_expand(char *content, int *end, t_prime *g_prime, int *env)
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
	substr = check_env(g_prime, substr, env);
	*end = i;
	return (substr);
}

char	*special_expand(char c, t_prime *g_prime, int *i)
{
	char	*substr;

	substr = NULL;
	*i += 1;
	if (c == '0')
		substr = ft_substr("minishell", 0, 9);
	if (c == '?')
		substr = ft_itoa(g_prime->exit_code);
	else
		*i -= 1;
	return (substr);
}

char	*dollar_analysis(char *content, int *end, t_prime *g_prime, int *env)
{
	int		i;
	int		start;
	char	*substr;

	i = *end;
	start = i + 1;
	substr = NULL;
	if (ret_null(content[++i]))
		substr = ft_strdup("");
	else if (put_directly(content[i]))
		substr = ft_substr(content, start - 1, 2);
	else if (put_synerror(content[i]))
		synerr_print(g_prime, "Syntax Error!\n");
	else if (special_chars(content[i]))
		substr = special_expand(content[i], g_prime, &i);
	else if (content[i] == '$')
		substr = ft_strdup("$");
	else if (chrchr_quotes(content[i]))
		substr = quotes_trim(content, &i, content[i]);
	else
		substr = dollar_expand(content, &i, g_prime, env);
	if (ret_null(content[i]) || put_directly(content[i]))
		i++;
	*end = i;
	return (substr);
}
