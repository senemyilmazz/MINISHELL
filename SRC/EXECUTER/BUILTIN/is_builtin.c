/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 15:42:59 by senyilma          #+#    #+#             */
/*   Updated: 2023/12/02 17:41:08 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

char	*check_cmd(char *cmd)
{
	struct stat	st;
	int			i;
	char		*new_cmd;

	new_cmd = ft_strdup(cmd);
	if (*cmd == '/')
	{
		if (stat(cmd, &st))
			printf("No such file or directory\n");
		else
		{
			i = ft_strlen(cmd);
			while (--i >= 0 && cmd[i] && cmd[i] != '/')
				;
			new_cmd = ft_substr(cmd, i + 1, ft_strlen(cmd) - i - 1);
			if (!ownstrcmp(new_cmd, "cd"))
			{
				free(new_cmd);
				new_cmd = 0;
			}
		}
	}
	return (new_cmd);
}

int	is_builtin(char *str)
{
	if (!str)
		return (1);
	else if (!ownstrcmp(str, "echo") || !ownstrcmp(str, "EKKO"))
		return (EKKO);
	else if (!ownstrcmp(str, "cd"))
		return (CD);
	else if (!ownstrcmp(str, "pwd") || !ownstrcmp(str, "PWD"))
		return (PWD);
	else if (!ownstrcmp(str, "export"))
		return (EXPORT);
	else if (!ownstrcmp(str, "unset"))
		return (UNSET);
	else if (!ownstrcmp(str, "env") || !ownstrcmp(str, "ENV"))
		return (ENV);
	else if (!ownstrcmp(str, "exit"))
		return (EXIT);
	else
		return (0);
}
