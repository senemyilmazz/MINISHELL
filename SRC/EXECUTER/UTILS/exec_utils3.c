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

int	search_path(t_env_l *env_l, char *str)
{
	t_env_l	*temp_env;

	temp_env = env_l;
	while (temp_env)
	{
		if (!ownstrcmp(temp_env->name, str))
			return (1);
		temp_env = temp_env->next;
	}
	return (0);
}

void	double_str_free(char **str)
{
	int	i;

	i = -1;
	while (str && str[++i])
		free(str[i]);
	free(str);
}

char	*get_command(t_prime *g_prime, t_parser *parser)
{
	char **path;
	int i;
	char *command;
	char cwd[256];

	i = -1;
	path = NULL;
	while (g_prime->path[++i])
		path = dynamic_malloc(path, ft_strjoin(g_prime->path[i],
					parser->command));
	i = -1;
	while (path[++i])
		if (!access(path[i], F_OK) && !access(path[i], X_OK))
			break ;
	command = ft_strdup(path[i]);
	if (!search_path(g_prime->env_l, "PATH"))
		command = parser->command;
	if (parser->command[0] == '.' && parser->command[1] == '/')
	{
		command = ft_strdup(getcwd(cwd, 256));
		command = ft_strjoin(command, ft_substr(parser->command, 1,
					ft_strlen(parser->command) - 1));
	}
	double_str_free(path);
	return (command);
}