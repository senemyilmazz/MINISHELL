/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 07:20:14 by senyilma          #+#    #+#             */
/*   Updated: 2023/11/08 16:55:59 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

void	type_match(t_lexer *temp)
{
	if (temp->type == SIGN_SIR && ft_strlen(temp->content) == 2)
		temp->type = SIGN_DIR;
	else if (temp->type == SIGN_SOR && ft_strlen(temp->content) == 2)
		temp->type = SIGN_DOR;
	else if (temp->type == SIGN_SIR && ft_strlen(temp->content) > 2)
		temp->type = -3;
	else if (temp->type == SIGN_PIPE && ft_strlen(temp->content) > 1)
		temp->type = -1;
	else if (temp->type == SIGN_SOR && ft_strlen(temp->content) > 2)
		temp->type = -2;
}

void	type_check(t_prime *g_prime)
{
	t_lexer	*temp;

	temp = g_prime->lexer;
	while (temp)
	{
		if (temp->type != 0)
			type_match(temp);
		temp = temp->next;
	}
}
