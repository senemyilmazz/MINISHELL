#include "../../../INCLUDE/minishell.h"

static int	is_all_numeric(char *text)
{
	while (text && *text)
	{
		if (!ft_isdigit(*text))
			return (0);
		text++;
	}
	return (1);
}

void	run_exit(t_prime *g_prime)
{
	int	array_len;

	if (g_prime->cmd_count == 1)
		printf("exit\n");
	array_len = parameters_count(&g_prime->parser->parameters[1]);
	if (array_len >= 1)
	{
		if (is_all_numeric(g_prime->parser->parameters[1]))
			g_prime->exit_code = ft_atoi(g_prime->parser->parameters[1]);
		else
			g_prime->exit_code = 255;
	}
	else if (array_len > 1)
	{
		printf("minikkus: exit: too many arguments\n");
		g_prime->exit_code = 1;
	}
	else
		g_prime->exit_code = 0;
	if (g_prime->exit_code == 255)
		printf("minikkus: exit: %s: numeric argument required\n", \
			g_prime->parser->parameters[1]);
	if (g_prime->cmd_count == 1)
		exit(g_prime->exit_code % 256);
}