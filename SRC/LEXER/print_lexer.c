/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 20:11:46 by senyilma          #+#    #+#             */
/*   Updated: 2023/11/07 18:44:04 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDE/minishell.h"

void	print_lexer(t_prime	*g_prime)
{
	t_lexer	*temp;

	temp = g_prime->lexer;
	while (temp)
	{
		printf("-----------lexer-----------\n");
		printf("C:%s\nT:%d\n", temp->content, temp->type);
		printf("---------------------------\n");
		temp = temp->next;
	}
}
