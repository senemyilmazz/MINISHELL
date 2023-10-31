/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 22:36:50 by senyilma          #+#    #+#             */
/*   Updated: 2023/11/01 02:11:37 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

int	chrchr_quotes(char c)
{
	return (c == D_QUOTES || c == S_QUOTES);
}

int	strchr_quotes(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (chrchr_quotes(str[i]))
			return (1);
	}
	return (0);
}
