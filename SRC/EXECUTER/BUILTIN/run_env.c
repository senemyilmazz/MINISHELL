#include "../../../INCLUDE/minishell.h"

void	run_env(t_prime* g_prime)
{
	t_env_l	*temp_env;

	temp_env = g_prime->env_l;
	while (temp_env)
	{
		if (temp_env->content)
		{
			write(g_prime->parser->outfile, temp_env->name,
				ft_strlen(temp_env->name));
			write(g_prime->parser->outfile, "=", 1);
			write(g_prime->parser->outfile, temp_env->content,
				ft_strlen(temp_env->content));
			write(g_prime->parser->outfile, "\n", 1);
		}
		temp_env = temp_env->next;
	}
}