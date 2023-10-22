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

void free_lexer(void)
{
	t_lexer *temp;

	while (g_prime.lexer)
	{
		temp = g_prime.lexer;
		g_prime.lexer = g_prime.lexer->next;
		free(temp);
	}
}

void	lexer(void)
{
	int		cmd_count;
	char	**lex_flist;
	t_list	*lex_slist;

	cmd_count = quotes_check(g_prime.line);
	if (cmd_count == -1)
	{
		print_error("tırnak açık\n");
		return ;
	}
	lex_flist = quotes_split(g_prime.line, cmd_count);
	lex_slist = wspace_split(lex_flist);
	create_nodes(lex_slist);
	if (syntax_check() == -1)
		free_lexer();
	while (g_prime.lexer)
	{
		printf("S:%s T:%d\n", g_prime.lexer->content, g_prime.lexer->type);
		g_prime.lexer = g_prime.lexer->next;
	}



	
	//type_init();
}
