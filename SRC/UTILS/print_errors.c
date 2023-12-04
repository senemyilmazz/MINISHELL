/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 21:39:21 by senyilma          #+#    #+#             */
/*   Updated: 2023/12/04 18:49:41 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDE/minishell.h"

int	synerr_print(t_prime *g_prime, char *str)
{
	printf("minikkus: syntax error near unexpected token '%s'\n", str);
	g_prime->exit_code = 258;
	return (-1);
}

void	file_error(char *filename, char *str, int *fd, t_prime *g_prime)
{
	printf("minikkus: %s: %s\n", filename, str);
	*fd = 2;
	g_prime->exit_code = 1;
}

void	print_error(t_prime *g_prime, char *str)
{
	printf("minikkus: %s", str);
	g_prime->exit_code = 258;
	return ;
}

void	command_error(char *arg, char *cmd, char *str, t_prime *g_prime)
{
	printf("minikkus: ");
	if (arg)
		printf("%s: ", arg);
	if (cmd)
		printf("%s: ", cmd);
	printf("%s\n", str);
	g_prime->exit_code = 1;
	g_prime->parser->outfile = 1;
}
