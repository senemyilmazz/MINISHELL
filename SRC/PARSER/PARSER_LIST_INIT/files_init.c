/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 00:39:48 by senyilma          #+#    #+#             */
/*   Updated: 2023/11/15 01:32:36 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

static void	file_err(t_parser *parser, t_expander *expander, char *filename)
{
	char	*fn;
	
	//if (*filename == '/' && expander->env == 1)
	//{
	//	printf("-minikkuş: '%s': is a directory\n", filename);
	//	(*parser)->infile = 2;
	//}
	if (expander->env == -1)
		printf("-minikkuş: %s: ambiguous redirect\n", expander->ex_content);
	else if (parser->infile < 2)
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

static void	search_file(char *filename, t_parser *parser, t_expander *expander)
{
	char	*pwd_file;
	char	*cwd;

	pwd_file = NULL;
	cwd = NULL;
	pwd_file = ft_strjoin(pwd_file, getcwd(cwd, 256));
	pwd_file = ft_strjoin(pwd_file, "/");
	pwd_file = ft_strjoin(pwd_file, filename);
	if (!access(pwd_file, F_OK))
		parser->infile = open(pwd_file, O_RDONLY, 0777);
	file_err(parser, expander, filename);
}

int	infile_init(t_expander *expander, t_parser *parser)
{
	if (expander->type == SIGN_SIR)
		search_file(expander->next->content, parser, expander->next);
	else if (expander->type == HEREDOC)
		parser->infile = -2;
	return (parser->infile);
}

int	outfile_init(t_expander *expander, t_parser *parser)
{
	if (expander->type == SIGN_SOR)
		parser->outfile = open(expander->next->content, \
				O_CREAT | O_RDWR | O_TRUNC, 0777);
	else if (expander->type == SIGN_DOR)
		parser->outfile = open(expander->next->content, O_CREAT | O_RDWR
				| O_APPEND, 0777);
	return (parser->outfile);
}
