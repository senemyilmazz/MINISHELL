#include "../../../INCLUDE/minishell.h"

int	is_all_numeric(char *text)
{
	while (text && *text)
	{
		if (!(*text >= '0' && *text <= '9'))
			return (0);
		text++;
	}
	return (1);
}

void	run_exit(t_prime *g_prime)
{
	int	array_len;

	array_len = parameters_count(&g_prime->parser->parameters[1]);
	if (array_len > 1)
	{
		print_error(0, "bash: exit: too many arguments\n");
		g_prime->exit_code = 1;
		return ;
	}
	else if (array_len == 1)
	{
		if (is_all_numeric(g_prime->parser->parameters[1]))
			g_prime->exit_code = ft_atoi(g_prime->parser->parameters[1]);
		else
		{
			print_error(0, "bash: exit: numeric argument required\n");
			g_prime->exit_code = 255;
		}
	}
	else
		g_prime->exit_code = 0;
	/*free_for_loop();
	free_core();*/
	exit(g_prime->exit_code % 256);
}