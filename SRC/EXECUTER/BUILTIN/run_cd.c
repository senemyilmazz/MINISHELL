#include "../../../INCLUDE/minishell.h"

int	update_pwd_from_export(t_prime *g_prime, char *pwd_name, char *pwd_content)
{
	t_env_l	*temp_env;
	char	*temp_pwd;

	if (!update_env(g_prime, pwd_name, pwd_content))
	{
		temp_env = g_prime->env_l;
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
	int		is_pwdaccess;
	char	*oldpwd;
	int		error;

	oldpwd = ft_strdup(getcwd(pwd, 256));
	error = chdir(parameters);
	if (!error && !search_path(g_prime->env_l, "OLDPWD"))
		env_lstadd_back(&g_prime->env_l, \
			env_listnew(ft_strdup("OLDPWD"), oldpwd));
	if (error == -1)
	{
		if (oldpwd)
			free(oldpwd);
		return (0);
	}
	if (!error && !ownstrcmp(g_prime->parser->parameters[1], "-"))
		printf("%s\n", parameters);
	is_pwdaccess = update_pwd_from_export(g_prime, "PWD", getcwd(pwd, 256));
	if (is_pwdaccess)
		update_pwd_from_export(g_prime, "OLDPWD", oldpwd);
	else
		delete_env(g_prime, "OLDPWD");
	return (1);
}

void	cd_two_arg(t_prime *g_prime)
{
	char	*path;

	path = NULL;
	if (!ownstrcmp(g_prime->parser->parameters[1], "-"))
	{
		if (!search_path(g_prime->env_l, "OLDPWD"))
		{
			print_error("cd: OLDPWD not set\n", 0);
			return ;
		}
		path = ft_strjoin(path, get_oldpwd(g_prime->env_l, "OLDPWD"));
	}
	else if (!ownstrcmp(g_prime->parser->parameters[1], "--"))
		path = ft_strjoin(path, get_oldpwd(g_prime->env_l, "HOME"));
	else
		path = ft_strjoin(path, g_prime->parser->parameters[1]);
	if (!change_dir(g_prime, path))
	{
		if (*g_prime->parser->parameters[1] == '-')
			print_error("cd: invalid option\n", 0);
		else
			print_error(" No such file or directory\n", 0);
		g_prime->parser->outfile = 1;
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
		if (ownstrcmp("HOME", temp_env->name))
		{
			content = temp_env->content;
			if (!content)
				return ;
			change_dir(g_prime, content);
			return ;
		}
		temp_env = temp_env->next;
	}
	print_error("cd: HOME not set\n", 0);
	g_prime->parser->outfile = 1;
}

void	run_cd(t_prime *g_prime)
{
	int	param_count;

	param_count = parameters_count(g_prime->parser->parameters);
	if (param_count > 2)
	{
		g_prime->parser->outfile = 1;
		print_error("cd: too many arguments", 0);
	}
	else if (param_count == 2)
		cd_two_arg(g_prime);
	else
		cd_one_arg(g_prime);
}
