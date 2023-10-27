/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 22:55:06 by senyilma          #+#    #+#             */
/*   Updated: 2023/10/27 15:55:10 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

void	create_nodes(t_list *lex_slist)
{
	t_list	*temp;

	temp = lex_slist;
	while (temp)
	{
		if (!strchr_metachar(temp->content))
			lexer_add_node(&g_prime.lexer, temp->content, 0);
		else
			metachar_split(temp->content);
		lex_slist = temp;
		temp = temp->next;
		free(lex_slist);
	}
}
