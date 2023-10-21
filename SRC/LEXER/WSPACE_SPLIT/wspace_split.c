/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wspace_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 03:24:26 by senyilma          #+#    #+#             */
/*   Updated: 2023/10/21 08:14:22 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

static int	wspace(char *str)
{
	if (ft_strchr(str, 9))
		return (9);
	if (ft_strchr(str, 10))
		return (10);
	if (ft_strchr(str, 13))
		return (13);
	if (ft_strchr(str, 32))
		return (32);
	return (0);
}

char	*lexer_trim(char const *s, char set)
{
	char	*cuttedstring;
	int		i;
	int		endofs;

	if (s != NULL)
	{
		i = 0;
		while (s[i] && s[i] == set)
			i++;
		endofs = ft_strlen(s) - 1;
		while (endofs > i && s[i] == set)
			endofs--;
		cuttedstring = ft_substr(s, i, endofs - i);
		return (cuttedstring);
	}
	return (NULL);
}

void	lexer_add_node(char *str, char c, int flag)
{
	if (flag == 1)
		lexer_lstadd_back(&g_prime.lexer, \
					lexer_listnew(ft_strdup(str)));
	if (flag == 2)
		lexer_lstadd_back(&g_prime.lexer, lexer_listnew \
		((ft_strdup(lexer_trim(str, c)))));
}

void	wspace_split(char **lex_list)
{
	int		i;
	int		j;
	char	**space_split;

	i = -1;
	while (lex_list[++i])
	{
		if (!ft_strchr(lex_list[i], D_QUOTES)
			&& !ft_strchr(lex_list[i], S_QUOTES))
		{
			space_split = ft_split(lex_list[i], wspace(lex_list[i]));
			j = -1;
			while (space_split[++j])
			{
				lexer_add_node(space_split[j], 0, 1);
				free(space_split[j]);
			}
		}
		else
			lexer_add_node(lex_list[i], *lex_list[i], 2);
		free(lex_list[i]);
	}
	free(space_split);
	free(lex_list);
}
