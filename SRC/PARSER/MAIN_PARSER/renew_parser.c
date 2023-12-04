/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renew_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 22:17:44 by senyilma          #+#    #+#             */
/*   Updated: 2023/12/04 21:03:51 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

static void	close_file(t_parser *parser)
{
	t_files		*iter_file;

	iter_file = parser->file;
	while (iter_file)
	{
		if (iter_file->fd != parser->outfile
			&& iter_file->fd != parser->infile)
			close(iter_file->fd);
		iter_file = iter_file->next;
	}
}

static int	files_init(t_expander **expand, t_parser *parser, t_prime *g_prime)
{
	int	fd;

	fd = 0;
	if ((*expand)->next->env == -1 && (*expand)->type != HEREDOC)
		file_error((*expand)->next->ex_content, \
			"ambiguous redirect", &fd, g_prime);
	else if ((*expand)->type == SIGN_SIR || (*expand)->type == HEREDOC)
		fd = infile_init(*expand, parser, g_prime);
	else if ((*expand)->type == SIGN_SOR || (*expand)->type == SIGN_DOR)
		fd = outfile_init(*expand, g_prime, parser);
	files_add_node(&parser->file, ft_strdup((*expand)->next->content), \
		(*expand)->type, fd);
	(*expand) = (*expand)->next;
	return (fd);
}

static void	parameters_init(t_parser *parser, char	*ex_content, int flag)
{
	parser->parameters = dynamic_malloc(parser->parameters, ex_content);
	if (!flag)
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
		starting = -1;
		while (temp_exp && temp_exp->type != SIGN_PIPE)
		{
			if (!(++starting) && temp_exp->type != TEXT)
				starting = 0;
			if (temp_exp->type == 0)
				parameters_init(temp_pars, temp_exp->content, starting);
			else
				if (files_init(&temp_exp, temp_pars, g_prime) == 2)
					temp_pars->command = NULL;
			temp_exp = temp_exp->next;
		}
		close_file(temp_pars);
		temp_pars = temp_pars->next;
		if (temp_exp)
			temp_exp = temp_exp->next;
	}
}
