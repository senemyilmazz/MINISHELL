/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 19:43:53 by senyilma          #+#    #+#             */
/*   Updated: 2023/11/08 08:20:58 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDE/minishell.h"

static t_parser	*parser_listnew(char **path, t_files *file, t_fd *fd)
{
	t_parser	*new;

	new = (t_parser *)ft_calloc(sizeof(t_parser), 1);
	if (!new)
		return (NULL);
	new->command = ft_strdup(*path);
	new->path = path;
	new->infile = fd->infile;
	new->outfile = fd->outfile;
	new->file = file;
	new->next = NULL;
	return (new);
}

static t_parser	*parser_lstlast(t_parser *lst)
{
	t_parser	*temp;

	if (!lst)
		return (0);
	temp = lst;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

static void	parser_lstadd_back(t_parser **lst, t_parser *new)
{
	if (new)
	{
		if (!(*lst))
		{
			*lst = new;
			return ;
		}
		parser_lstlast(*lst)->next = new;
		new->next = 0;
	}
}

void	parser_addnode(t_parser **parser, char **path, t_files *file, t_fd *fd)
{
	parser_lstadd_back(parser, parser_listnew(path, file, fd));
}
