/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renew_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 22:17:44 by senyilma          #+#    #+#             */
/*   Updated: 2023/11/20 18:46:47 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

int	filename_error(t_expander **expander)
{
	t_expander	*next;

	next = (*expander)->next;
	if (next->env == -1)
		printf("-minikkuş: %s: ambiguous redirect\n", next->ex_content);
	else if (!*(*expander)->next->content)
		printf("-minikkuş: %s: No such file or directory\n", "");
	else if (*next->content == '/' && next->env == 1
		&& (*expander)->type != HEREDOC && (*expander)->type != SIGN_SIR)
		printf("-minikkuş: '%s': is a directory\n", next->content);
	//else if (*next->content == '/' && (*expander)->type != HEREDOC
	//	&& (*expander)->type != SIGN_SIR)
	//	printf("-minikkuş: '%s': Permission denied\n", next->content);
	else
		return (0);
	return (2);
}

static int	files_init(t_expander **expander, t_parser *parser)
{
	int	fd;

	fd = 0;
	if (filename_error(expander))
		fd = 2;
	else if ((*expander)->type == SIGN_SIR || (*expander)->type == HEREDOC)
		fd = infile_init(*expander, parser);
	else if ((*expander)->type == SIGN_SOR || (*expander)->type == SIGN_DOR)
		fd = outfile_init(*expander, parser);
	files_add_node(&parser->file, ft_strdup((*expander)->next->content), \
		(*expander)->type, fd);
	(*expander) = (*expander)->next;
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
				if (files_init(&temp_exp, temp_pars) == 2)
					return (free_parser(&g_prime->parser));
			temp_exp = temp_exp->next;
		}
		temp_pars = temp_pars->next;
		if (temp_exp)
			temp_exp = temp_exp->next;
	}
}
