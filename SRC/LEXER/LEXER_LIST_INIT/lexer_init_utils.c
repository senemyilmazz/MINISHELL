/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 03:42:36 by senyilma          #+#    #+#             */
/*   Updated: 2023/10/31 18:45:24 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

t_lexer	*lexer_listnew(char *content, int type)
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

char	*lexer_trim(char const *s, char set)
{
	char	*cuttedstring;
	int		i;
	int		endofs;

	if (s != NULL)
	{
		i = 0;
		while (s[i] && s[i] == set)
			i++;
		endofs = ft_strlen(s) - 1;
		while (endofs > i && s[i] == set)
			endofs--;
		cuttedstring = ft_substr(s, i, endofs - i);
		return (cuttedstring);
	}
	return (NULL);
}

void	lexer_add_node(t_lexer **lexer, char *str, int type)
{
	lexer_lstadd_back(lexer, \
		lexer_listnew(ft_strdup(str), type));
}
