/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 01:09:01 by senyilma          #+#    #+#             */
/*   Updated: 2023/10/21 08:09:46 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

void	lexer(void)
{
	int		cmd_count;
	char	**lex_list;

	cmd_count = quotes_check(g_prime.line);
	if (cmd_count == -1)
	{
		print_error("tırnak açık\n");
		return ;
	}
	lex_list = quotes_split(g_prime.line, cmd_count);
	wspace_split(lex_list);
	type_init();
	while (g_prime.lexer)
	{
		printf("%s %d\n", g_prime.lexer->content, g_prime.lexer->type);
		g_prime.lexer = g_prime.lexer->next;
	}
}
