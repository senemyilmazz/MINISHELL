/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 05:34:05 by senyilma          #+#    #+#             */
/*   Updated: 2023/12/10 19:39:17 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

int	update_pwd_from_export(t_prime *g_prime, char *pwd_name, char *pwd_content)
{
	char	*temp_pwd;

	if (!update_env(g_prime, pwd_name, pwd_content))
	{
		temp_pwd = NULL;
		temp_pwd = ft_strjoin(temp_pwd, pwd_name);
		temp_pwd = ft_strjoin(temp_pwd, "=");
		temp_pwd = ft_strjoin(temp_pwd, pwd_content);
		add_newenv(g_prime, temp_pwd);
		free(temp_pwd);
		return (0);
	}
	return (1);
}

int	change_dir(t_prime *g_prime, char *parameters)
{
	char	pwd[256];
	char	*oldpwd;
	int		error;

	oldpwd = ft_strdup(getcwd(pwd, 256));
	error = chdir(parameters);
	if (!error && !search_path(g_prime->env_l, "OLDPWD"))
		env_lstadd_back(&g_prime->env_l, env_listnew(ft_strdup("OLDPWD"),
				ft_strdup(oldpwd)));
	if (error == -1)
	{
		oldpwd = free_null(oldpwd);
		return (0);
	}
	if (!error && !ownstrcmp(g_prime->parser->parameters[1], "-"))
		printf("%s\n", parameters);
	update_pwd_from_export(g_prime, "PWD", getcwd(pwd, 256));
	update_pwd_from_export(g_prime, "OLDPWD", oldpwd);
	oldpwd = free_null(oldpwd);
	return (1);
}

void	cd_two_arg(t_prime *g_prime)
{
	char	*path;

	path = NULL;
	if (!ownstrcmp(g_prime->parser->parameters[1], "-"))
	{
		if (!search_path(g_prime->env_l, "OLDPWD"))
			if (command_error(0, "cd", "OLDPWD not set", g_prime))
				return ;
		path = ft_strjoin(path, get_oldpwd(g_prime->env_l, "OLDPWD"));
	}
	else if (!ownstrcmp(g_prime->parser->parameters[1], "--"))
		path = ft_strjoin(path, get_oldpwd(g_prime->env_l, "HOME"));
	else
		path = ft_strjoin(path, g_prime->parser->parameters[1]);
	if (!change_dir(g_prime, path))
	{
		if (*g_prime->parser->parameters[1] == '-')
			command_error(g_prime->parser->parameters[1], "cd",
				"invalid option", g_prime);
		else
			command_error(g_prime->parser->parameters[1], "cd",
				" No such file or directory", g_prime);
	}
	free(path);
}

void	cd_one_arg(t_prime *g_prime)
{
	t_env_l	*temp_env;
	char	*content;

	temp_env = g_prime->env_l;
	while (temp_env)
	{
		if (!ownstrcmp("HOME", temp_env->name))
		{
			content = temp_env->content;
			if (!content)
				return ;
			change_dir(g_prime, content);
			return ;
		}
		temp_env = temp_env->next;
	}
	command_error(0, "cd", "HOME not set\n", g_prime);
}

void	run_cd(t_prime *g_prime)
{
	int	param_count;

	g_prime->exit_code = 0;
	param_count = parameters_count(g_prime->parser->parameters);
	if (!search_path(g_prime->env_l, "PWD"))
		delete_env(g_prime, "PWD");
	if (param_count > 1)
		cd_two_arg(g_prime);
	else
		cd_one_arg(g_prime);
}
