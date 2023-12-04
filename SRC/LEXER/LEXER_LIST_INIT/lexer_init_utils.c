/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 03:42:36 by senyilma          #+#    #+#             */
/*   Updated: 2023/12/03 22:29:09 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

static t_lexer	*lexer_listnew(char *content, int type)
{
	t_lexer	*new;

	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->content = content;
	new->type = type;
	new->next = NULL;
	return (new);
}

static t_lexer	*lexer_lstlast(t_lexer	*lst)
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

static void	lexer_lstadd_back(t_lexer	**lst, t_lexer	*new)
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

void	lexer_add_node(t_lexer **lexer, char *str, int type)
{
	lexer_lstadd_back(lexer, \
		lexer_listnew(ft_strdup(str), type));
}
