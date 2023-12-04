/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 05:34:36 by senyilma          #+#    #+#             */
/*   Updated: 2023/12/04 05:34:37 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

void	run_pwd(t_prime *g_prime, t_parser *parser)
{
	char	cwd[256];
	char	*pwd;

	pwd = getcwd(cwd, 256);
	write(parser->outfile, pwd, ft_strlen(pwd));
	write(parser->outfile, "\n", 1);
	g_prime->exit_code = 0;
}
