#include "../../../INCLUDE/minishell.h"

int	update_pwd_from_export(t_prime *g_prime, char *pwd_name, char *pwd_content)
{
	t_env_l	*temp_env;
	char	*temp_pwd;

	if (!update_env(g_prime, pwd_name, pwd_content))
	{
		temp_env = g_prime->env_l;
		temp_pwd = NULL;
		own_strjoin(&temp_pwd, pwd_name);
		str_addchar(&temp_pwd, '=');
		own_strjoin(&temp_pwd, pwd_content);
		add_newenv(&temp_env, temp_pwd);
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
	if (error == -1)
	{
		if (oldpwd)
			free(oldpwd);
		return (0);
	}
	is_pwdaccess = update_pwd_from_export(g_prime, "PWD", getcwd(pwd, 256));
	if (is_pwdaccess)
		update_pwd_from_export(g_prime, "OLDPWD", oldpwd);
	else
		delete_env(g_prime, "OLDPWD");
	if (oldpwd)
		free(oldpwd);
	//change_title();
	return (1);
}

void	cd_two_arg(t_prime *g_prime)
{
	if (!change_dir(g_prime, g_prime->parser->parameters[1]))
	{
		print_error(0, "--minikkus: No such file or directory\n");
		g_prime->parser->outfile = 1;
		return ;
	}
}

void	cd_one_arg(t_prime *g_prime)
{
	t_env_l	*temp_env;
	char	*content;

	temp_env = g_prime->env_l;
	while (temp_env)
	{
		if (str_compare("HOME", temp_env->name))
		{
			content = temp_env->content;
			if (!content)
				return ;
			change_dir(g_prime, content);
			return ;
		}
		temp_env = temp_env->next;
	}
	print_error(0, "-bash: HOME not set\n");
	g_prime->parser->outfile = 1;
}

void	run_cd(t_prime *g_prime)
{
	int	param_count;

	param_count = parameters_count(g_prime->parser->parameters);
	if (param_count > 2)
	{
		g_prime->parser->outfile = 1;
		print_error(0, "too many arguments");
	}
	else if (param_count == 2)
		cd_two_arg(g_prime);
	else
		cd_one_arg(g_prime);
}