/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renew_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 22:17:44 by senyilma          #+#    #+#             */
/*   Updated: 2023/11/10 18:55:16 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

static void	search_file(char *filename, t_parser **parser)
{
	char	*pwd_file;
	char	*cwd;

	pwd_file = NULL;
	cwd = NULL;
	pwd_file = ft_strjoin(pwd_file, getcwd(cwd, 256));
	pwd_file = ft_strjoin(pwd_file, "/");
	pwd_file = ft_strjoin(pwd_file, filename);
	if (!access(pwd_file, F_OK))
		(*parser)->infile = open(pwd_file, O_RDONLY, 0777);
	if ((*parser)->infile < 2)
	{
		printf("-minikkuş: '%s': No such file or directory\n", filename);
		(*parser)->infile = 2;
	}
	if (*filename == '/')
	{
		printf("-minikkuş: '%s': is a directory\n", filename);
		(*parser)->infile = 2;
	}
}

static int	files_init(t_expander **expander, t_parser *parser)
{
	if ((*expander)->type != HEREDOC)
	{
		if ((*expander)->type == SIGN_SOR)
		{
			parser->outfile = open((*expander)->next->content, O_CREAT | O_RDWR
					| O_TRUNC, 0777);
		}
		else if ((*expander)->type == SIGN_DOR)
		{
			parser->outfile = open((*expander)->next->content, O_CREAT | O_RDWR
					| O_APPEND, 0777);
		}
		else if ((*expander)->type == SIGN_SIR)
			search_file((*expander)->next->content, &parser);
		files_add_node(&parser->file, ft_strdup((*expander)->next->content), \
			(*expander)->type, parser->infile);
	}
	(*expander) = (*expander)->next;
	return (parser->infile);
}

static void	parameters_init(t_parser *parser, char	*ex_content, int flag)
{
	parser->parameters = dynamic_malloc(parser->parameters, ex_content);
	if (flag)
		parser->command = ft_strdup(*parser->parameters);
}

void	renew_parser(t_prime *g_prime)
{
	t_expander	*temp_exp;
	t_parser	*temp_pars;
	int			starting;

	temp_exp = g_prime->expander;
	temp_pars = g_prime->parser;
	while (temp_exp)
	{
		starting = 0;
		while (temp_exp && temp_exp->type != SIGN_PIPE)
		{
			if (!(starting++) && temp_exp->type != TEXT)
				starting = 0;
			if (temp_exp->type == 0)
				parameters_init(temp_pars, temp_exp->content, starting);
			else
				if (files_init(&temp_exp, temp_pars) == 2)
					return (free_parser(&g_prime->parser));
			temp_exp = temp_exp->next;
		}
		temp_pars = temp_pars->next;
		if (temp_exp)
			temp_exp = temp_exp->next;
	}
}
