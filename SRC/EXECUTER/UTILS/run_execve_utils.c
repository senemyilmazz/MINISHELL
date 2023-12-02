#include "../../../INCLUDE/minishell.h"

char	**get_env_cpy(t_prime *g_prime)
{
	char	**envlist;
	char	*temp_env;
	t_env_l	*temp_envlist;

	envlist = NULL;
	temp_envlist = g_prime->env_l;
	while (temp_envlist)
	{
		if (temp_envlist->content)
		{
			temp_env = NULL;
			temp_env = ft_strjoin(temp_env, temp_envlist->name);
			temp_env = ft_strjoin(temp_env, "=");
			temp_env = ft_strjoin(temp_env, temp_envlist->content);
			envlist = dynamic_malloc(envlist, temp_env);
		}
		temp_envlist = temp_envlist->next;
	}
	return (envlist);
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
	if (str)
		free(str);
}

char	*get_command(t_prime *g_prime, t_parser *pars)
{
	char	**path;
	int		i;
	char	*command;
	char	cwd[256];

	i = -1;
	path = NULL;
	while (g_prime->path[++i])
		path = dynamic_malloc(path, ft_strjoin(g_prime->path[i],
					pars->command));
	i = -1;
	while (path[++i])
		if (!access(path[i], F_OK) && !access(path[i], X_OK))
			break ;
	command = ft_strdup(path[i]);
	if (!search_path(g_prime->env_l, "PATH"))
		command = pars->command;
	if (pars->command[0] == '.' && pars->command[1] == '/')
	{
		command = ft_strdup(getcwd(cwd, 256));
		command = ft_strjoin(command, ft_substr(pars->command, 1,
					ft_strlen(pars->command) - 1));
	}
	double_str_free(path);
	return (command);
}
