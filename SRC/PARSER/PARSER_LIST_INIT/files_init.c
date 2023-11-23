/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 00:39:48 by senyilma          #+#    #+#             */
/*   Updated: 2023/11/23 04:52:20 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

static void	infile_error(t_parser *parser, t_expander *expander, char *filename)
{
	char	*fn;

	if (parser->infile < 2 || !*expander->content)
	{
		if (expander->ex_content)
			fn = expander->ex_content;
		else if (*filename == '\\')
			fn = filename + 1;
		else
			fn = filename;
		printf("-minikkuş: %s: No such file or directory\n", fn);
	}
	parser->infile = 2;
}

int	infile_init(t_expander *expander, t_parser *parser)
{
	char	*pwd_file;
	char	*cwd;

	cwd = NULL;
	if (expander->type == SIGN_SIR)
	{
		infile_error(parser, expander->next, expander->next->content);
		pwd_file = ft_strdup(expander->next->content);
		if (*expander->next->content != '/')
		{
			pwd_file = ft_strjoin(pwd_file, getcwd(cwd, 256));
			pwd_file = ft_strjoin(pwd_file, "/");
			pwd_file = ft_strjoin(pwd_file, expander->next->content);
		}
		if (!access(pwd_file, F_OK))
			parser->infile = open(pwd_file, O_RDONLY, 0777);
		infile_error(parser, expander->next, expander->next->content);
		free (pwd_file);
	}
	if (expander->type == HEREDOC)
		parser->infile = -2;
	return (parser->infile);
}

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
