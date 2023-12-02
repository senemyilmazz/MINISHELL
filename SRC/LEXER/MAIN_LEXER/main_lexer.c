/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 01:09:01 by senyilma          #+#    #+#             */
/*   Updated: 2023/12/02 10:40:47 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

void	lexer(t_prime *g_prime)
{
	t_list	*lex_slist;
	t_list	*lex_mlist;

	if (quotes_check(g_prime->line) == -1)
	{
		print_error("incorrect use of quotes!\n", 0);
		g_prime->exit_code = 258;
		return ;
	}
	lex_slist = wspace_split(g_prime->line, 0, 0, 0);
	lex_mlist = metachar_split(lex_slist);
	create_nodes(g_prime, lex_mlist);
	if (syntax_check(g_prime) == -1)
	{
		g_prime->exit_code = 258;
		free_lexer(&g_prime->lexer);
	}
}
