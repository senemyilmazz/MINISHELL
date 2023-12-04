/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 23:04:18 by senyilma          #+#    #+#             */
/*   Updated: 2023/12/04 13:25:35 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

int	ret_null(char c)
{
	return ((c >= '1' && c <= '9') || c == '*' || c == '@' || c == '!');
}

int	put_directly(char c, int *i)
{
	if (c == '%' || c == '+' || c == ',' || c == '.' || c == '/'
		|| c == ':' || c == '=' || c == ']' || c == '^' || c == '}'
		|| c == '~' || c == ' ')
	{
		*i += 1;
		return (1);
	}
	if (c == '\0' || chrchr_quotes(c))
		return (1);
	return (0);
}

int	put_synerror(char c)
{
	return (c == '(' || c == '[' || c == 92 || c == '{' || c == ')'
		|| c == ';' || c == '#' || c == '-');
}

int	special_chars(char c)
{
	return (c == '0' || c == '?');
}
