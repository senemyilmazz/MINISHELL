/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 23:01:38 by mkati             #+#    #+#             */
/*   Updated: 2023/11/09 22:23:38 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

static void	heredoc_count(t_expander *expander, t_parser *parser)
{
	t_expander	*temp;
	int			heredoc_c;

	temp = expander;
	heredoc_c = 0;
	while (temp && temp->type != 1)
	{
		if (temp->type == HEREDOC)
			heredoc_c++;
		temp = temp->next;
	}
	if (heredoc_c != 0)
	{
		parser->heredoc = (char **)malloc(sizeof(char *) * (heredoc_c + 1));
		if (!parser->heredoc)
			return ;
		parser->heredoc[heredoc_c] = 0;
	}
}

static void	heredoc_read(t_parser *parser, char *end, int i)
{
	char	*str;

	str = 0;
	parser->heredoc[i] = 0;
	while (1)
	{
		str = readline("> ");
		if (ft_strncmp(str, end, ft_strlen(str)) == 0)
			break ;
		parser->heredoc[i] = parse_strjoin(parser->heredoc[i], str);
	}
}

void	heredoc_init(t_prime *g_prime)
{
	t_expander	*temp_ex;
	t_parser	*temp_parser;
	int			i;

	temp_ex = g_prime->expander;
	temp_parser = g_prime->parser;
	while (temp_ex)
	{
		i = 0;
		heredoc_count(temp_ex, temp_parser);
		while (temp_ex && temp_ex->type != 1)
		{
			if (temp_ex->type == HEREDOC)
				heredoc_read(temp_parser, temp_ex->next->content, i++);
			temp_ex = temp_ex->next;
		}
		if (temp_ex)
			temp_ex = temp_ex->next;
		temp_parser = temp_parser->next;
	}
}
