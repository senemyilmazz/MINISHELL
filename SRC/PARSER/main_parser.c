/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 03:24:25 by senyilma          #+#    #+#             */
/*   Updated: 2023/11/08 17:07:40 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDE/minishell.h"

void	redirection(t_expander *temp, t_files **file, t_fd *fd)
{
	if (temp->type == SIGN_SOR)
		fd->outfile = open(temp->next->content, O_CREAT | O_RDWR
				| O_TRUNC, 0777);
	else if (temp->type == SIGN_DOR)
		fd->outfile = open(temp->next->content, O_CREAT | O_RDWR
				| O_APPEND, 0777);
	//INFILE İÇİN ACCESS() KONTROLÜ YAPMALISIN!
	else if (temp->type == SIGN_SIR)
		fd->infile = open(temp->next->content, O_RDONLY, 0777);
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
	//HEREDOC VAR MI DİYE BURADA KONTROL ETMELİSİMN!! HEREDOC KAPANANA KADAR ÖNCESİNDEKİ DOSYALAR OLUŞTURULMAZ!! 
	//PIPE'tan sonra dahi olsa önceki noddaki dosyalar olulturulmamalı! 
	//heredocları node da tuttuğumuz için heredoc kontrolünden önce nodeların oluşmuş olması gerekiyor!! aşağıdaki gibi olmaz :(
	while (temp)
	{
		while (temp && temp->type != 1)
		{
			if (temp->type > 0 && temp->type != 4)
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
