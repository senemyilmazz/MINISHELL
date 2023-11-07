/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_init_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:58:32 by senyilma          #+#    #+#             */
/*   Updated: 2023/11/07 16:54:01 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDE/minishell.h"

static t_expander	*expander_listnew(char *content, int type)
{
	t_expander	*new;

	new = (t_expander *)malloc(sizeof(t_expander));
	if (!new)
		return (NULL);
	new->content = content;
	new->type = type;
	new->next = NULL;
	return (new);
}

static t_expander	*expander_lstlast(t_expander *lst)
{
	t_expander	*temp;

	if (!lst)
		return (0);
	temp = lst;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

static void	expander_lstadd_back(t_expander **lst, t_expander *new)
{
	if (new)
	{
		if (!(*lst))
		{
			*lst = new;
			return ;
		}
		expander_lstlast(*lst)->next = new;
		new->next = 0;
	}
}

void	expander_add_node(t_expander **expander, char *str, int type)
{
	expander_lstadd_back(expander, expander_listnew(str, type));
}
