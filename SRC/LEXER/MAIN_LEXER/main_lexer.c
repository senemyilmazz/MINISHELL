/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 01:09:01 by senyilma          #+#    #+#             */
/*   Updated: 2023/10/27 15:57:29 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

void	free_lexer(void)
{
	t_lexer	*temp;

	while (g_prime.lexer)
	{
		temp = g_prime.lexer;
		g_prime.lexer = g_prime.lexer->next;
		free(temp);
	}
}

void	lexer(void)
{
	t_list	*lex_slist;

	if (quotes_check(g_prime.line) == -1)
	{
		print_error("incorrect use of quotes\n");
		return ;
	}
	lex_slist = wspace_split(g_prime.line, 0, 0, 0);
		//while (lex_slist)
		//{
		//	printf("aaa:    %s\n", lex_slist->content);
		//	lex_slist = lex_slist->next;
		//}
	create_nodes(lex_slist);
	if (syntax_check() == -1)
		free_lexer();
	while (g_prime.lexer)
	{
		printf("----------------------\n");
		printf("S:%s	T:%d\n", g_prime.lexer->content, g_prime.lexer->type);
		printf("----------------------\n");
		g_prime.lexer = g_prime.lexer->next;
	}
}
