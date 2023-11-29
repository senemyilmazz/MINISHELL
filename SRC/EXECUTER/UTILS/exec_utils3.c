#include "../../../INCLUDE/minishell.h"

char	*check_cmd(char *cmd)
{
	struct stat	st;
	int			i;
	char		*new_cmd;

	new_cmd = cmd;
	if (*cmd == '/')
	{
		if (stat(cmd, &st))
			printf("No such file or directory\n");
		else
		{
			i = ft_strlen(cmd);
			while (--i >= 0 && cmd[i] && cmd[i] != '/')
				;
			new_cmd = ft_substr(cmd, i + 1, ft_strlen(cmd) - i - 1);
			if (!ownstrcmp(new_cmd, "cd"))
			{
				free(new_cmd);
				new_cmd = 0;
			}
		}
	}
	return (new_cmd);
}

/*void	change_title(t_prime *g_prime)
{
	char	cwd[256];

	if (g_prime->title->full_title)
		free(g_prime->title->full_title);
	g_prime->title->full_title = NULL;
	own_strjoin(g_prime->title->full_title, g_prime->title->head);
	own_strjoin(g_prime->title->full_title, (char *)getcwd(cwd, 256));
	own_strjoin(g_prime->title->full_title, "$ ");
}*/