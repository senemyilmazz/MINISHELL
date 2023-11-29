#include "../../../INCLUDE/minishell.h"

void	run_unset(t_prime *g_prime)
{
	char	**temp_name;
	int		array_len;

	array_len = parameters_count(g_prime->parser->parameters);
	if (array_len > 1)
	{
		temp_name = g_prime->parser->parameters;
		while (*(++temp_name))
		{
			if (!env_arg_control(g_prime, *temp_name))
			{
				print_error(0, "-bash: unset: not a valid identifier\n");
				g_prime->exit_code = 1;
				continue ;
			}
			else
				delete_env(g_prime, *temp_name);
		}
	}
}

void	delete_env(t_prime *g_prime, char *name)
{
	t_env_l	*env;
	t_env_l	*temp_env;

	env = g_prime->env_l;
	while (env)
	{
		if (str_compare(env->name, name))
		{
			if (env->content)
				free(env->content);
			free(env->name);
			if (g_prime->env_l == env)
				g_prime->env_l = g_prime->env_l->next;
			else
				temp_env->next = env->next;
			free(env);
			break ;
		}
		temp_env = env;
		env = env->next;
	}
}