/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 03:24:25 by senyilma          #+#    #+#             */
/*   Updated: 2023/12/05 18:58:49 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

void	parser(t_prime *g_prime)
{
	if (!g_prime->expander)
		return ;
	parser_addnode(&g_prime->parser, pipe_count(g_prime));
	heredoc_init(g_prime);
	if (!g_prime->parser)
		return ;
	renew_parser(g_prime);
}
