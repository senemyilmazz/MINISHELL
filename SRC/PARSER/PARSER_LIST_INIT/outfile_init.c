/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 09:44:32 by senyilma          #+#    #+#             */
/*   Updated: 2023/11/23 09:44:54 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

void	outfile_error(char *str, char *filename, t_parser *parser)
{
	printf("-minikkus :%s: %s", filename, str);
	parser->outfile = 2;
}

void	directory_check(char *filename, t_parser *parser)
{
	struct stat	st;
	char		*path_dir;
	int			i;

	if (stat(filename, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
			outfile_error("is a directory!\n", filename, parser);
	}
	else
	{
		i = ft_strlen(filename);
		while (--i >= 0 && filename[i] && filename[i] != '/')
			;
		path_dir = ft_substr(filename, 0, i + 1);
		if (stat(path_dir, &st) == 0)
		{
			if (S_ISDIR(st.st_mode))
				if (ownstrcmp(path_dir, "/") || ownstrcmp(path_dir, "/Users/"))
					outfile_error("permission denied!\n", filename, parser);
		}
		else
			outfile_error("No such file or directory!\n", filename, parser);
		free(path_dir);
	}
}

int	outfile_init(t_expander *expander, t_parser *parser)
{
	char	*filename;

	filename = expander->next->content;
	if (*expander->next->content == '\\')
		filename = expander->next->content + 1;
	directory_check(filename, parser);
	if (parser->outfile != 2)
	{
		if (expander->type == SIGN_SOR)
			parser->outfile = open(filename, \
					O_CREAT | O_RDWR | O_TRUNC, 0777);
		else if (expander->type == SIGN_DOR)
			parser->outfile = open(filename, O_CREAT | O_RDWR
					| O_APPEND, 0777);
	}
	return (parser->outfile);
}
