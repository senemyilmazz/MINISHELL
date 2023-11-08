/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:43:27 by senyilma          #+#    #+#             */
/*   Updated: 2023/11/07 18:47:05 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDE/minishell.h"

void	print_expander(t_prime	*g_prime)
{
	t_expander	*temp;

	temp = g_prime->expander;
	while (temp)
	{
		printf("----------expander------------\n");
		printf("C:%s\nT:%d\n", temp->content, temp->type);
		printf("------------------------------\n");
		temp = temp->next;
	}
}
