/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renew_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 22:17:44 by senyilma          #+#    #+#             */
/*   Updated: 2023/12/12 00:01:08 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

static void	close_file(t_parser *parser)
{
	t_files	*iter_file;

	iter_file = parser->file;
	while (iter_file)
	{
		if (iter_file->fd != parser->outfile && iter_file->fd != parser->infile)
			close(iter_file->fd);
		iter_file = iter_file->next;
	}
}

static int	files_init(t_expander **exp, t_parser *pars, t_prime *g_prime,
		int *fd)
{
	if (*fd == 2)
		return (0);
	else if ((*exp)->next->env == -1 && (*exp)->type != HEREDOC)
		file_error((*exp)->next->ex_content, "ambiguous redirect", fd,
			g_prime);
	else if ((*exp)->type == SIGN_SIR || (*exp)->type == HEREDOC)
		*fd = infile_init(*exp, pars, g_prime);
	else if ((*exp)->type == SIGN_SOR || (*exp)->type == SIGN_DOR)
		*fd = outfile_init(*exp, g_prime, pars);
	files_add_node(&pars->file, ft_strdup((*exp)->next->content), (*exp)->type,
		*fd);
	(*exp) = (*exp)->next;
	return (*fd);
}

static void	parameters_init(t_parser *parser, char *ex_content)
{
	if (!parser->command)
		parser->command = ft_strdup(ex_content);
	parser->parameters = dynamic_malloc(parser->parameters, ex_content);
}

void	init_values(t_prime *g_prime, t_parser *pars, t_expander **exp, int *fd)
{
	while ((*exp) && (*exp)->type != SIGN_PIPE)
	{
		if ((*exp)->type == 0)
			parameters_init(pars, (*exp)->content);
		else if (files_init(&(*exp), pars, g_prime, fd) == 2)
			pars->command = free_null(pars->command);
		(*exp) = (*exp)->next;
	}
}

void	renew_parser(t_prime *g_prime)
{
	t_expander	*temp_exp;
	t_parser	*temp_pars;
	int			fd;

	temp_exp = g_prime->expander;
	temp_pars = g_prime->parser;
	while (temp_exp)
	{
		fd = 0;
		init_values(g_prime, temp_pars, &temp_exp, &fd);
		close_file(temp_pars);
		temp_pars = temp_pars->next;
		if (temp_exp)
			temp_exp = temp_exp->next;
	}
}
