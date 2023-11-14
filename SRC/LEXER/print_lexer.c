/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 20:11:46 by senyilma          #+#    #+#             */
/*   Updated: 2023/11/15 01:51:07 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDE/minishell.h"

void	print_lexer(t_prime	*g_prime)
{
	t_lexer	*temp;

	temp = g_prime->lexer;
	printf("\n-----------{ LEXER }-----------\n");
	while (temp)
	{
		printf("C:%s\nT:%d\n", temp->content, temp->type);
		printf("-------------------------------\n");
		temp = temp->next;
	}
	printf("\n\n");
}
