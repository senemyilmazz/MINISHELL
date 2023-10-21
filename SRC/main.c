/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:50:48 by senyilma          #+#    #+#             */
/*   Updated: 2023/10/21 08:11:34 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"

void	print_error(char *str)
{
	printf("%s", str);
}

//int	metachar(char *s)
//{
//	if (*s == '|')
//		return (1);
//	if (*s == '<')
//		return (2);
//	if (*s == '>')
//		return (3);
//	return (0);
//}





void	ft_readline(void)
{
	while (1)
	{
		g_prime.line = readline("minikkus> ");
		add_history(g_prime.line);
		lexer();
		free(g_prime.line);
	}
}

int	main(int argc, char **argv, char **env)
{
	(void)env;
	(void)argc;
	(void)argv;
	ft_readline();
}
