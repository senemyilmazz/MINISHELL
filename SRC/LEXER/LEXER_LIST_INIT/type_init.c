/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 07:20:14 by senyilma          #+#    #+#             */
/*   Updated: 2023/10/21 07:36:22 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

static int	type_match(char *content)
{
	if (*content == PIPE)
		return (1);
	else if (*content == SIR && *(content + 1) == SIR)
		return (4);
	else if (*content == SIR)
		return (2);
	else if (*content == SOR && *(content + 1) == SOR)
		return (5);
	else if (*content == SOR)
		return (3);
	else
		return (0);
}

void	type_init(void)
{
	t_lexer	*temp;

	temp = g_prime.lexer;
	while (temp)
	{
		temp->type = type_match(temp->content);
		temp = temp->next;
	}
}
