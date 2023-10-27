/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 07:20:14 by senyilma          #+#    #+#             */
/*   Updated: 2023/10/27 04:37:57 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

void	type_match(t_lexer *temp)
{
	if (temp->type == 3 && ft_strlen(temp->content) == 2)
		temp->type = 4;
	else if (temp->type == 2 && ft_strlen(temp->content) == 2)
		temp->type = 5;
	else if (temp->type == 3 && ft_strlen(temp->content) == 3)
		temp->type = 6;
	else if (temp->type == 1 && ft_strlen(temp->content) > 1)
		temp->type = -1;
	else if (temp->type == 2 && ft_strlen(temp->content) > 2)
		temp->type = -2;
	else if (temp->type == 3 && ft_strlen(temp->content) > 3)
		temp->type = -3;
}

void	type_check(void)
{
	t_lexer	*temp;

	temp = g_prime.lexer;
	while (temp)
	{
		if (temp->type != 0)
			type_match(temp);
		temp = temp->next;
	}
}
