/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 01:18:14 by senyilma          #+#    #+#             */
/*   Updated: 2023/10/23 15:55:39 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

static void	quotes_split2(char *str, int *start, int *end, char c)
{
	*end = *start;
	(*end)++;
	while (str[*end] && str[*end] != c)
		(*end)++;
	(*end)++;
}

char	**quotes_split(char *str, int size)
{
	char	**lexer_list;
	int		end;
	int		start;
	int		lexer_i;

	lexer_list = (char **)malloc(sizeof(char *) * (size + 1));
	if (!lexer_list)
		return (0);
	end = 0;
	lexer_i = -1;
	while (++lexer_i < size)
	{
		start = end;
		if (chrchr_quotes(str[start]))
			quotes_split2(str, &start, &end, str[start]);
		else
		{
			while (str[end] && !chrchr_quotes(str[end]))
				end++;
		}
		lexer_list[lexer_i] = ft_substr(str, start, end - start);
	}
	lexer_list[lexer_i] = 0;
	return (lexer_list);
}
