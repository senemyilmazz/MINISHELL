/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:29:10 by senyilma          #+#    #+#             */
/*   Updated: 2023/11/01 19:01:31 by senyilma         ###   ########.fr       */
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
			str = NULL;
		iter = iter->next;
	}
	free (substr);
	return (str);
}

char	*straight_expand(t_prime *g_prime, char *content, int *end)
{
	int		i;
	int		start;
	char	*joinedstr;
	char	*substr;

	joinedstr = NULL;
	i = *end;
	while (content[i])
	{
		start = i;
		if (content[i] != '$')
		{
			while (content[i] && content[i] != '$')
				i++;
			substr = ft_substr(content, start, i - start);
		}
		else
		{
			start = i + 1;
			while (content[++i] && (ft_isalpha(content[i]) || ft_isdigit(content[i])))
				;
			substr = ft_substr(content, start, i - start);
			substr = check_env(g_prime, substr);
		}
		joinedstr = ft_strjoin(joinedstr, substr);
	}
	*end = i;
	if (content[i] != '\0')
		*end = i + 1;
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
			start = i + 1;
			while (content[++i] && (ft_isdigit(content[i]) || ft_isalpha(content[i])))
				;
			substr = ft_substr(content, start, i - start);
			substr = check_env(g_prime, substr);
		}
		joinedstr = ft_strjoin(joinedstr, substr);
	}
	*end = i;
	if (content[i] != '\0')
		*end = i + 1;
	return (joinedstr);
}

char	*s_quotes_trim(char *content, int *end)
{
	int		i;
	int		start;
	char	*substr;

	i = *end + 1;
	start = i;
	while (content[i] && content[i] != S_QUOTES)
		i++;
	substr = ft_substr(content, start, i - start);
	*end = i;
	if (content[i] != '\0')
		*end = i + 1;
	return (substr);
}

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
			substr = s_quotes_trim(content, &end);
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

void	expander(t_prime *g_prime)
{
	t_lexer	*temp;

	temp = g_prime->lexer;
	while (temp)
	{
		if (!ft_strchr(temp->content, '$'))
			expander_add_node(&g_prime->expander, temp->content, temp->type);
		else
			expander_add_node(&g_prime->expander, \
				expand_content(g_prime, temp->content), temp->type);
		temp = temp->next;
	}
	while (g_prime->expander)
	{
		printf("%s\n", g_prime->expander->content);
		g_prime->expander = g_prime->expander->next;
	}
}
