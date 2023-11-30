#include "../../../INCLUDE/minishell.h"

int	n_control(char *str)
{
	int	i;

	i = -1;
	if (str[++i] == '-')
	{
		while (str[++i])
			if (str[i] != 'n')
				return (0);
	}
	else
		return (0);
	return (1);
	
}

void	run_echo(t_prime* g_prime)
{
	char	**path;
	int		is_n;

	is_n = 0;
	path = &g_prime->parser->parameters[1];
	while (*path && n_control(*path) == 1)
	{
		is_n = 1;
		path++;
	}
	while (*path)
	{
		if (*path)
			write(g_prime->parser->outfile, *path, ft_strlen(*path));
		if (*(++path))
			write(g_prime->parser->outfile, " ", 1);
	}
	if (!is_n)
		write(g_prime->parser->outfile, "\n", 1);
}