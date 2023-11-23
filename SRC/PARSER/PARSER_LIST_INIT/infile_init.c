/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 00:39:48 by senyilma          #+#    #+#             */
/*   Updated: 2023/11/23 10:06:51 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

int	infile_init(t_expander *expander, t_parser *parser)
{
	struct stat	st;
	char		*fn;

	if (expander->type == SIGN_SIR)
	{
		fn = expander->next->content;
		if (expander->ex_content)
			fn = expander->ex_content;
		else if (*expander->next->content == '\\')
			fn = expander->next->content + 1;
		if (stat(expander->next->content, &st) != 0)
		{
			printf("-minikkuş: %s: No such file or directory\n", fn);
			parser->infile = 2;
		}
		else
			parser->infile = open(fn, O_RDONLY, 0777);
	}
	if (expander->type == HEREDOC)
		parser->infile = -2;
	return (parser->infile);
}
