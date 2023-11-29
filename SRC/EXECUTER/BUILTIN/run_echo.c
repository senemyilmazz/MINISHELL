#include "../../../INCLUDE/minishell.h"

void	run_echo(t_prime* g_prime)
{
	char	**path;
	int		is_n;

	is_n = 0;
	path = &g_prime->parser->parameters[1];
	while (*path && ft_strncmp(*path, "-n", ft_strlen(*path)) == 0)
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