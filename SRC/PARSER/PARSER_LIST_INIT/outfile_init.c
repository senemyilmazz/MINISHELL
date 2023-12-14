/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 00:24:23 by senyilma          #+#    #+#             */
/*   Updated: 2023/12/11 19:55:07 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

void	directory_check(char *filename, t_prime *g_prime, t_parser *parser)
{
	struct stat	st;
	char		*path;
	int			i;
	int			*fd;

	fd = &parser->outfile;
	if (!stat(filename, &st) && S_ISDIR(st.st_mode))
		file_error(filename, "is a directory!", fd, g_prime);
	else if (stat(filename, &st) != 0)
	{
		i = ft_strlen(filename);
		while (--i >= 0 && filename[i] && filename[i] != '/')
			;
		path = ft_substr(filename, 0, i + 1);
		if (stat(path, &st) != 0 && ft_strchr(path, '/'))
			file_error(filename, "No such file or directory", fd, g_prime);
		else if (stat(path, &st) == 0)
			if (S_ISDIR(st.st_mode))
				if (!ownstrcmp(path, "/") || !ownstrcmp(path, "/Users/"))
					file_error(filename, "Permission denied", fd, g_prime);
		free(path);
	}
}

int	outfile_init(t_expander *expander, t_prime *g_prime, t_parser *parser)
{
	char	*filename;
	int		*fd;

	fd = &parser->outfile;
	filename = expander->next->content;
	if (*expander->next->content == '\\')
		filename = expander->next->content + 1;
	directory_check(filename, g_prime, parser);
	if (*fd != 2)
	{
		if (expander->type == SIGN_SOR)
			*fd = open(filename, \
					O_CREAT | O_RDWR | O_TRUNC, 0777);
		else if (expander->type == SIGN_DOR)
			*fd = open(filename, O_CREAT | O_RDWR
					| O_APPEND, 0777);
	}
	return (*fd);
}
