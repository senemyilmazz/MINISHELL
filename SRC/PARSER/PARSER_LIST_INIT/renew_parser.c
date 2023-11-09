/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renew_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 22:17:44 by senyilma          #+#    #+#             */
/*   Updated: 2023/11/10 01:28:28 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

int	search_file(char *filename)
{
	(void)filename;
	return (1);
}

static void	files_init(t_expander **expander, t_parser *parser)
{
	if ((*expander)->type != HEREDOC)
	{
		if ((*expander)->type == SIGN_SOR)
			parser->outfile = open((*expander)->next->content, O_CREAT | O_RDWR
					| O_TRUNC, 0777);
		else if ((*expander)->type == SIGN_DOR)
			parser->outfile = open((*expander)->next->content, O_CREAT | O_RDWR
					| O_APPEND, 0777);
		else if ((*expander)->type == SIGN_SIR)
		{
			if (!search_file((*expander)->content))
				return ;
			parser->infile = open((*expander)->next->content, O_RDONLY, 0777);
		}
		files_add_node(&parser->file, \
			ft_strdup((*expander)->next->content), (*expander)->type);
	}
	(*expander) = (*expander)->next;
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
	int			flag;

	temp_exp = g_prime->expander;
	temp_pars = g_prime->parser;
	while (temp_exp)
	{
		flag = 1;
		starting = 0;
		while (temp_exp && temp_exp->type != SIGN_PIPE)
		{
			if (!(starting++) && temp_exp->type != TEXT)
				flag = 0;
			if (temp_exp->type > 0)
				files_init(&temp_exp, temp_pars);
			else
				parameters_init(temp_pars, temp_exp->content, flag);
			temp_exp = temp_exp->next;
		}
		temp_pars = temp_pars->next;
		if (temp_exp)
			temp_exp = temp_exp->next;
	}
}
