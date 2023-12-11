/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 00:19:55 by senyilma          #+#    #+#             */
/*   Updated: 2023/12/11 00:19:58 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

void	run_export(t_prime *g_prime, t_parser *parser)
{
	int		array_len;
	char	**temp_path;

	g_prime->exit_code = 0;
	array_len = parameters_count(parser->parameters);
	if (array_len > 1)
	{
		temp_path = parser->parameters;
		while (*(++temp_path))
			double_export_arg(g_prime, *temp_path);
	}
	else
		single_export_arg(g_prime, parser);
}

void	single_export_arg(t_prime *g_prime, t_parser *parser)
{
	t_env_l	*env;

	env = g_prime->env_l;
	while (env)
	{
		write(parser->outfile, "declare -x ", 11);
		write(parser->outfile, env->name, ft_strlen(env->name));
		if (!env->content)
		{
			write(parser->outfile, "\n", 1);
			env = env->next;
			continue ;
		}
		write(parser->outfile, "=\"", 2);
		write(parser->outfile, env->content, ft_strlen(env->content));
		write(parser->outfile, "\"\n", 2);
		env = env->next;
	}
}

int	change_env(t_prime *g_prime, char *envname, char *arg, int is_equal)
{
	t_env_l	*env;

	env = g_prime->env_l;
	while (env)
	{
		if (!ownstrcmp(envname, env->name))
		{
			if (is_equal)
				update_env(g_prime, envname, arg);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

void	double_export_arg(t_prime *g_prime, char *env_cmd)
{
	char	*arg;
	int		is_equal;
	t_env_l	*env;
	char	*temp_envname;

	if (!env_arg_control(g_prime, env_cmd))
	{
		g_prime->exit_code = 1;
		return ;
	}
	temp_envname = get_env_name(env_cmd);
	arg = env_cmd + ft_strlen(temp_envname);
	is_equal = 0;
	if (*arg == '=')
		is_equal |= 1;
	if (change_env(g_prime, temp_envname, ++arg, is_equal))
	{
		free(temp_envname);
		return ;
	}
	env = g_prime->env_l;
	add_newenv(g_prime, env_cmd);
	if (!is_equal)
		update_env(g_prime, env_cmd, NULL);
	free(temp_envname);
}
