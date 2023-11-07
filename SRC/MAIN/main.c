/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:50:48 by senyilma          #+#    #+#             */
/*   Updated: 2023/11/03 14:59:33 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDE/minishell.h"

void	print_error(char *str)
{
	printf("%s", str);
	return ;
}

void	prime_init(t_prime *g_prime)
{
	g_prime->lexer = (t_lexer *)malloc(sizeof(t_lexer));
	g_prime->expander = (t_expander *)malloc(sizeof(t_expander));
	g_prime->parser = (t_parser *)malloc(sizeof(t_parser));
	if (!g_prime->lexer
		|| !g_prime->expander || !g_prime->parser)
		return ;
	g_prime->line = NULL;
	g_prime->lexer = NULL;
	g_prime->expander = NULL;
	g_prime->parser = NULL;
}

void	ft_readline(t_prime *g_prime)
{
	while (1)
	{
		prime_init(g_prime);
		g_prime->line = readline("minikkus> ");
		add_history(g_prime->line);
		lexer(g_prime);
		expander(g_prime);
		//parser(g_prime);
		//executer(g_prime);
		free_prime(g_prime);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_prime	*g_prime;

	(void)env;
	(void)argc;
	(void)argv;
	g_prime = (t_prime *)malloc(sizeof(t_prime));
	g_prime->env_l = (t_env_l *)malloc(sizeof(t_env_l));
	g_prime->env_l = NULL;
	env_init(g_prime, env);
	ft_readline(g_prime);
}
