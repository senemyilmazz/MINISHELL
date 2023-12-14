/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:50:48 by senyilma          #+#    #+#             */
/*   Updated: 2023/12/11 18:06:42 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDE/minishell.h"

void	prime_init(t_prime *g_prime)
{
	g_prime->fd = NULL;
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
		if (g_prime->line && *g_prime->line != 0)
			add_history(g_prime->line);
		if (g_prime->line == NULL)
		{
			printf("minikkus> exit\n");
			exit(g_prime->exit_code);
		}
		lexer(g_prime);
		expander(g_prime);
		parser(g_prime);
		executer(g_prime, 0);
		free_prime(g_prime);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_prime	*g_prime;

	(void)argc;
	(void)argv;
	g_prime = (t_prime *)malloc(sizeof(t_prime));
	g_prime->env_l = NULL;
	g_prime->exit_code = 0;
	g_signal = 0;
	env_init(g_prime, env);
	signal_init();
	ft_readline(g_prime);
}
