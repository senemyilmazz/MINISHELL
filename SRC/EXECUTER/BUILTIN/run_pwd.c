#include "../../../INCLUDE/minishell.h"

void	run_pwd(t_parser *parser)
{
	char	cwd[256];
	char	*pwd;

	pwd = getcwd(cwd, 256);
	write(parser->outfile, pwd, ft_strlen(pwd));
	write(parser->outfile, "\n", 1);
}
