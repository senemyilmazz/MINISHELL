#include "../../../INCLUDE/minishell.h"

int	env_name_control(char *env)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (!env || env[i] == ' ' || env[i] == '=')
		return (0);
	if (ft_isalpha(env[i]))
		flag = 1;
	while (env[i] != ' ' && env[i] && env[i] != '=')
		if (ft_isdigit(env[i++]) && !flag)
			return (0);
	if (!env || (env[i] != '=' && env[i]))
		return (0);
	return (1);
}

int	env_arg_control(t_prime *g_prime, char *env)
{
	if (env_name_control(env))
		return (1);
	print_error(env, "export: not a valid identifier\n");
	g_prime->exit_code = 1;
	return (0);
}
