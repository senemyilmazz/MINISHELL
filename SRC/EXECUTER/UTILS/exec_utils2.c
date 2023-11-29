#include "../../../INCLUDE/minishell.h"

int	update_env(t_prime *g_prime, char *env_name, char *new_arg)
{
	t_env_l	*env;

	env = g_prime->env_l;
	while (env)
	{
		if (str_compare(env->name, env_name))
		{
			if (env->content)
				free(env->content);
			env->content = NULL;
			if (!new_arg)
				return (1);
			own_strjoin(&env->content, new_arg);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

char	*get_env_name(char *content)
{
	int		env_name_len;
	char	*name;
	char	*temp_name;

	env_name_len = get_env_name_count(content);
	if (!env_name_len)
		return (NULL);
	name = (char *)malloc(sizeof(char) * (env_name_len + 1));
	temp_name = name;
	while (content && *content && *content != '=')
		*(temp_name++) = *(content++);
	*temp_name = 0;
	return (name);
}

int	get_env_name_count(char *env_arg)
{
	int	count;

	count = 0;
	while (env_arg && *env_arg && *(env_arg++) != '=')
		count++;
	return (count);
}

t_env_l	*add_newenv(t_env_l **env_l, char *env)
{
	t_env_l	*last_node;
	char	*content;

	if (!*env_l)
	{
		*env_l = (t_env_l *)malloc(sizeof(t_env_l));
		last_node = *env_l;
	}
	else
	{
		last_node = *env_l;
		while (last_node->next)
			last_node = last_node->next;
		last_node->next = (t_env_l *)malloc(sizeof(t_env_l));
		last_node = last_node->next;
	}
	last_node->name = get_env_name(env);
	content = env + ft_strlen(last_node->name);
	if (*content == '=' && *(content + 1))
		last_node->content = ft_strdup(content + 1);
	else
		last_node->content = NULL;
	last_node->next = NULL;
	return (last_node);
}