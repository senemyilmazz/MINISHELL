/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 00:39:48 by senyilma          #+#    #+#             */
/*   Updated: 2023/11/20 18:46:40 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

static void	file_err(t_parser *parser, t_expander *expander, char *filename)
{
	char	*fn;

	if (parser->infile < 2)
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

static char	*search_file(char *filename)
{
	char	*pwd_file;
	char	*cwd;

	cwd = NULL;
	pwd_file = ft_strdup(filename);
	if (*filename != '/')
	{
		pwd_file = ft_strjoin(pwd_file, getcwd(cwd, 256));
		pwd_file = ft_strjoin(pwd_file, "/");
		pwd_file = ft_strjoin(pwd_file, filename);
	}
	return (pwd_file);
}

int	infile_init(t_expander *expander, t_parser *parser)
{
	char	*pwd_file;

	if (expander->type == SIGN_SIR)
	{
		pwd_file = search_file(expander->next->content);
		if (!access(pwd_file, F_OK))
			parser->infile = open(pwd_file, O_RDONLY, 0777);
	}
	else if (expander->type == HEREDOC)
		parser->infile = -2;
	file_err(parser, expander, expander->next->content);
	return (parser->infile);
}

int	outfile_init(t_expander *expander, t_parser *parser)
{
	char	*filename;
	char	*pwd_file;

	filename = expander->next->content;
	if (*expander->next->content == '\\')
		filename = expander->next->content + 1;
	pwd_file = search_file(expander->next->content);
	if (!access(pwd_file, F_OK) && *filename == '/')
	{
		printf("-minikkuş: %s: is a directory\n", filename);
		parser->outfile = 2;
	}
	//else if (!access(filename, F_OK) && *filename == '/')
	//	printf("-minikkuş: '%s': Permission denied\n", filename);
	else if (expander->type == SIGN_SOR)
		parser->outfile = open(filename, \
				O_CREAT | O_RDWR | O_TRUNC, 0777);
	else if (expander->type == SIGN_DOR)
		parser->outfile = open(filename, O_CREAT | O_RDWR
				| O_APPEND, 0777);
	return (parser->outfile);
}
