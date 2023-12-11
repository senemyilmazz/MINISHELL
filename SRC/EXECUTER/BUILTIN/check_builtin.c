/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 15:42:59 by senyilma          #+#    #+#             */
/*   Updated: 2023/12/11 03:38:30 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

int	stat_check(t_prime *g_prime, char *cmd)
{
	struct stat	st;

	if ((*cmd == '/' || *cmd == '.') && stat(cmd, &st))
	{
		g_prime->exit_code = 127;
		perror("minikkus ");
	}
	else if ((*cmd == '/' || *cmd == '.')
		&& !stat(cmd, &st) && S_ISDIR(st.st_mode))
	{
		command_error(cmd, 0, "is a directory", g_prime);
		g_prime->exit_code = 126;
	}
	else
		return (1);
	return (0);
}

static char	*check_cmd(char *cmd)
{
	int			i;
	char		*new_cmd;

	new_cmd = NULL;
	if (*cmd == '/')
	{
		i = ft_strlen(cmd);
		while (--i >= 0 && cmd[i] && cmd[i] != '/')
			;
		new_cmd = ft_substr(cmd, i + 1, ft_strlen(cmd) - i - 1);
		if (!ownstrcmp(new_cmd, "cd"))
			new_cmd = free_null(new_cmd);
	}
	else
		new_cmd = ft_strdup(cmd);
	return (new_cmd);
}

static int	is_builtin(char *str)
{
	if (!str)
		return (-1);
	else if (*str == 48)
		return (1);
	else if (!ownstrcmp(str, "echo") || !ownstrcmp(str, "EKKO"))
		return (EKKO);
	else if (!ownstrcmp(str, "cd"))
		return (CD);
	else if (!ownstrcmp(str, "pwd") || !ownstrcmp(str, "PWD"))
		return (PWD);
	else if (!ownstrcmp(str, "env") || !ownstrcmp(str, "ENV"))
		return (ENV);
	else if (!ownstrcmp(str, "unset"))
		return (UNSET);
	else if (!ownstrcmp(str, "export"))
		return (EXPORT);
	else if (!ownstrcmp(str, "exit"))
		return (EXIT);
	else
		return (0);
}

int	check_builtin(t_prime *g_prime, t_parser *parser)
{
	char	*cmd;
	int		builtin_ret;

	if (parser->command)
	{
		if (!stat_check(g_prime, parser->command))
			return (2);
		cmd = check_cmd(parser->command);
		builtin_ret = is_builtin(cmd);
		if (cmd)
			free(cmd);
	}
	else
		builtin_ret = -1;
	return (builtin_ret);
}
