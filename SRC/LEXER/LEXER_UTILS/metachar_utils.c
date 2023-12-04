/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metachar_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 19:49:05 by senyilma          #+#    #+#             */
/*   Updated: 2023/11/09 22:58:23 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

int	chrchr_metachar(char c)
{
	if (c == PIPE)
		return (SIGN_PIPE);
	else if (c == SOR)
		return (SIGN_SOR);
	else if (c == SIR)
		return (SIGN_SIR);
	else
		return (TEXT);
}

int	strchr_metachar(char *content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (chrchr_metachar(content[i]))
			return (1);
		i++;
	}
	return (0);
}
