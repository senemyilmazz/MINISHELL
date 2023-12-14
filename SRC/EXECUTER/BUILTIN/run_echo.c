/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 00:19:29 by senyilma          #+#    #+#             */
/*   Updated: 2023/12/11 22:12:37 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

static int	n_control(char *str)
{
	int	i;

	i = -1;
	if (str[++i] == '-')
	{
		if (str[i + 1] != 'n')
			return (0);
		while (str[++i])
			if (str[i] != 'n')
				return (0);
	}
	else
		return (0);
	return (1);
}

void	run_echo(t_prime *g_prime, t_parser *parser)
{
	char	**path;
	int		nl;

	g_prime->exit_code = 0;
	nl = 0;
	path = &parser->parameters[1];
	while (*path && n_control(*path) == 1)
	{
		nl = 1;
		path++;
	}
	while (*path)
	{
		if (*path)
			write(parser->outfile, *path, ft_strlen(*path));
		if (*(++path))
			write(parser->outfile, " ", 1);
	}
	if (!nl)
		write(parser->outfile, "\n", 1);
}
