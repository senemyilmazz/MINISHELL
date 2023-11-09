/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 03:24:25 by senyilma          #+#    #+#             */
/*   Updated: 2023/11/09 22:24:33 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

void	parser(t_prime *g_prime)
{
	if (!g_prime->expander)
		return ;
	parser_addnode(&g_prime->parser, pipe_count(g_prime->expander));
	heredoc_init(g_prime);
	renew_parser(g_prime);
}
