/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 23:04:18 by senyilma          #+#    #+#             */
/*   Updated: 2023/11/07 18:02:14 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDE/minishell.h"

int	ret_null(char c)
{
	return ((c >= '1' && c <= '9') || c == '*' || c == '@' || c == '!');
}

int	put_directly(char c)
{
	return (c == '%' || c == '+' || c == ',' || c == '.' || c == '/'
		|| c == ':' || c == '=' || c == ']' || c == '^' || c == '}'
		|| c == '~');
}

char	*put_synerror(char c)
{
	if (c == '(' || c == '[' || c == 92 || c == '{' || c == ')'
		|| c == ';' || c == '#' || c == '-')
		printf("Syntax Error!\n");
	return (NULL);
}

int	special_chars(char c)
{
	return (c == '0' || c == '?');
}
