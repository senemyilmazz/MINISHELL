#include "../../../INCLUDE/minishell.h"

void	run_export(t_prime *g_prime)
{
	int		array_len;
	char	**temp_path;

	array_len = parameters_count(g_prime->parser->parameters);
	if (array_len > 1)
	{
		temp_path = g_prime->parser->parameters;
		while (*(++temp_path))
			double_export_arg(g_prime, *temp_path);
	}
	else
		single_export_arg(g_prime);
}

void	double_export_arg(t_prime *g_prime, char *env_cmd)
{
	char	*arg;
	int		is_equal;
	t_env_l	*env;
	char	*temp_envname;

	if (!env_arg_control(g_prime, env_cmd))
		return ;
	temp_envname = get_env_name(env_cmd);
	arg = env_cmd + ft_strlen(temp_envname);
	is_equal = 0;
	if (*arg == '=')
		is_equal |= 1;
	if (change_env(g_prime, temp_envname, ++arg, is_equal))
	{
		free(temp_envname);
		return ;
	}
	env = g_prime->env_l;
	add_newenv(&env, env_cmd);
	if (!is_equal)
		update_env(g_prime, env_cmd, NULL);
	free(temp_envname);
}

void	single_export_arg(t_prime *g_prime)
{
	t_env_l	*env;

	env = g_prime->env_l;
	while (env)
	{
		write(g_prime->parser->outfile, "declare -x ", 11);
		write(g_prime->parser->outfile, env->name, ft_strlen(env->name));
		if (!env->content)
		{
			write(g_prime->parser->outfile, "\n", 1);
			env = env->next;
			continue ;
		}
		write(g_prime->parser->outfile, "=\"", 2);
		write(g_prime->parser->outfile, env->content, ft_strlen(env->content));
		write(g_prime->parser->outfile, "\"\n", 2);
		env = env->next;
	}
}

int	change_env(t_prime *g_prime, char *envname, char *arg, int is_equal)
{
	t_env_l	*env;

	env = g_prime->env_l;
	while (env)
	{
		if (str_compare(envname, env->name))
		{
			if (is_equal)
				update_env(g_prime, envname, arg);
			return (1);
		}
		env = env->next;
	}
	return (0);
}
