#include "../../../INCLUDE/minishell.h"

static int	n_control(char *str)
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

void	run_echo(t_parser *parser)
{
	char	**path;
	int		nl;

	nl = 0;
	path = &parser->parameters[1];
	while (*path && n_control(*path) == 1)
	{
		nl = 1;
		path++;
	}
	while (*path)
	{
		if (*path)
			write(parser->outfile, *path, ft_strlen(*path));
		if (*(++path))
			write(parser->outfile, " ", 1);
	}
	if (!nl)
		write(parser->outfile, "\n", 1);
}
