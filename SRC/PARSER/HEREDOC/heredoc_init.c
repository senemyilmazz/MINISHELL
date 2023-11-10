/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 23:01:38 by mkati             #+#    #+#             */
/*   Updated: 2023/11/10 14:58:17 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

static void	heredoc_read(t_parser *parser, char *end)
{
	char	*str;

	str = 0;
	if (parser->heredoc)
		free(parser->heredoc);
	parser->heredoc = 0;
	while (1)
	{
		str = readline("> ");
		if (!pars_strcmp(str, end))
			break ;
		parser->heredoc = pars_strjoin(parser->heredoc, str);
	}
}

void	heredoc_init(t_prime *g_prime)
{
	t_expander	*temp_ex;
	t_parser	*temp_parser;

	temp_ex = g_prime->expander;
	temp_parser = g_prime->parser;
	while (temp_ex)
	{
		while (temp_ex && temp_ex->type != 1)
		{
			if (temp_ex->type == HEREDOC)
				heredoc_read(temp_parser, temp_ex->next->content);
			temp_ex = temp_ex->next;
		}
		if (temp_ex)
			temp_ex = temp_ex->next;
		temp_parser = temp_parser->next;
	}
}