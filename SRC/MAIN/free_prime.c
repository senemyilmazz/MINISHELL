/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_prime.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 22:08:33 by senyilma          #+#    #+#             */
/*   Updated: 2023/11/15 01:55:27 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDE/minishell.h"

void	free_lexer(t_lexer **lexer)
{
	t_lexer	*temp;

	if (!lexer)
		return ;
	while (*lexer)
	{
		temp = (*lexer)->next;
		free((*lexer)->content);
		free(*lexer);
		*lexer = 0;
		*lexer = temp;
	}
}

void	free_expander(t_expander **expander)
{
	t_expander	*temp;

	if (!expander)
		return ;
	while (*expander)
	{
		temp = (*expander)->next;
		free((*expander)->content);
		free(*expander);
		*expander = 0;
		*expander = temp;
	}
}

void	free_file(t_parser **parser)
{
	t_files	*temp;

	while ((*parser)->file)
	{
		temp = (*parser)->file->next;
		free ((*parser)->file->filename);
		free ((*parser)->file);
		(*parser)->file = temp;
	}
	free ((*parser)->file);
	(*parser)->file = 0;
}

void	free_parser(t_parser **parser)
{
	t_parser	*temp;
	int			i;

	if (!parser)
		return ;
	while (*parser)
	{
		temp = (*parser)->next;
		free((*parser)->command);
		i = -1;
		while ((*parser)->parameters && (*parser)->parameters[++i])
			free((*parser)->parameters[i]);
		free ((*parser)->parameters);
		if ((*parser)->heredoc)
			free((*parser)->heredoc);
		if ((*parser)->file)
			free_file(parser);
		free(*parser);
		*parser = 0;
		*parser = temp;
	}
}

//static void	free_env_l(t_env_l **env)
//{
//	t_env_l	*temp;

//	if (!env)
//		return ;
//	while (*env)
//	{
//		temp = (*env)->next;
//		free((*env)->content);
//		free((*env)->name);
//		free(*env);
//		*env = 0;
//		*env = temp;
//	}
//}

void	free_prime(t_prime *g_prime)
{
	free_lexer(&g_prime->lexer);
	free_expander(&g_prime->expander);
	free_parser(&g_prime->parser);
	//free_env_l(&g_prime->env_l);
	free(g_prime->line);
}
