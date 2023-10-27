/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metachar_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:04:38 by senyilma          #+#    #+#             */
/*   Updated: 2023/10/27 15:50:58 by senyilma         ###   ########.fr       */
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

	end = 0;
	while (content[end])
	{
		start = end;
		if (chrchr_metachar(content[start]))
			while (content[end] && content[end] == content[start])
				end++;
		else
		{
			while (content[end] && !chrchr_metachar(content[end]))
			{
				if (chrchr_quotes(content[start]))
				{
					end++;
					while (content[end] && content[end] != content[start])
						end++;
					end++;
				}
				else
					end++;
			}
		}
		str = ft_substr(content, start, end - start);
		lexer_add_node(&g_prime.lexer, str, chrchr_metachar(*str));
		free(str);
	}
}
