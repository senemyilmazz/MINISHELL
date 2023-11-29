#include "../../../INCLUDE/minishell.h"

void	run_pwd(t_prime* g_prime)
{
	char	cwd[256];
	char	*pwd;

	pwd = getcwd(cwd, 256);
	write(g_prime->parser->outfile, pwd, ft_strlen(pwd));
	write(g_prime->parser->outfile, "\n", 1);
}