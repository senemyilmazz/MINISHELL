/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:43:27 by senyilma          #+#    #+#             */
/*   Updated: 2023/11/15 01:51:13 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDE/minishell.h"

void	print_expander(t_prime	*g_prime)
{
	t_expander	*temp;

	temp = g_prime->expander;
	printf("\n---------{ EXPANDER }----------\n");
	while (temp)
	{
		printf("C:%s\nT:%d\n", temp->content, temp->type);
		printf("%d\n", temp->env);
		if (temp->ex_content)
			printf("ex_cont:%s\n", temp->ex_content);
		printf("-------------------------------\n");
		temp = temp->next;
	}
	printf("\n\n");
}
