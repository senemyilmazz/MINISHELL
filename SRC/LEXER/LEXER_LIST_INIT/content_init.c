/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 03:42:36 by senyilma          #+#    #+#             */
/*   Updated: 2023/10/21 07:00:56 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

t_lexer	*lexer_listnew(char *content)
{
	t_lexer	*new;

	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->content = content;
	new->type = 0;
	new->next = NULL;
	return (new);
}

t_lexer	*lexer_lstlast(t_lexer	*lst)
{
	t_lexer	*temp;

	if (!lst)
		return (0);
	temp = lst;
	while (temp->next != 0)
	{
		temp = temp->next;
	}
	return (temp);
}

void	lexer_lstadd_back(t_lexer	**lst, t_lexer	*new)
{
	if (new)
	{
		if (!(*lst))
		{
			*lst = new;
			return ;
		}
		lexer_lstlast(*lst)->next = new;
		new->next = 0;
	}
}
