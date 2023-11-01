/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 03:24:25 by senyilma          #+#    #+#             */
/*   Updated: 2023/11/01 14:07:10 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDE/minishell.h"

void	cr_parser_node(t_prime *g_prime)
{
	
}

void	pipe_split(t_prime	*g_prime)
{
	t_lexer	*temp;
	char	**com_arg;
	int		count;
	int		type;
	char	**str

	temp = g_prime->lexer;
	while (temp)
	{
		count = 0;
		while (temp && temp->type != 1)
		{
			if (temp->type == 0)
			{
				while (temp && temp->type == 0)
				{
					count++;
					temp = temp->next;
				}
			}
			if (temp->type > 1)
				temp = temp->next;
		}
		str = (char **)malloc(sizeof(char) * count + 1);
		temp = temp->next;
	}
}


void	parser(t_prime *g_prime)
{
	pipe_split(g_prime);	
}
