/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 03:24:25 by senyilma          #+#    #+#             */
/*   Updated: 2023/11/07 23:15:45 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDE/minishell.h"

void	redirection(t_expander *temp, t_files **file, t_fd *fd)
{
	if (temp->type == 2) // '>'
		fd->outfile = open(temp->next->content, O_CREAT | O_RDWR
				| O_TRUNC, 0777);
	else if (temp->type == 5) // '>>'
		fd->outfile = open(temp->next->content, O_CREAT | O_RDWR
				| O_APPEND, 0777);
	else if (temp->type == 3) // '<'
		fd->infile = open(temp->next->content, O_RDONLY, 0777);
	else
		fd->infile = open("heredoc", O_CREAT | O_RDWR
				| O_APPEND, 0777);
	files_add_node(file, ft_strdup(temp->next->content), temp->type);
}

void	parser(t_prime *g_prime)
{
	t_expander	*temp;
	char		**path;
	t_files		*file;
	t_fd		*fd;

	fd = (t_fd *)malloc(sizeof(t_fd));
	if (!fd)
		return ;
	file = NULL;
	temp = g_prime->expander;
	path = NULL;
	while (temp)
	{
		while (temp && temp->type != 1)
		{
			if (temp->type > 0)
			{
				redirection(temp, &file, fd);
				temp = temp->next;
			}
			else
				path = dynamic_malloc(path, temp->content);
			temp = temp->next;
		}
		parser_addnode(&g_prime->parser, path, file, fd);
		path = NULL;
		file = NULL;
		fd->outfile = 1;
		if (temp)
			temp = temp->next;
	}
}
