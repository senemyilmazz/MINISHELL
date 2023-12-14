/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_prime.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 22:08:33 by senyilma          #+#    #+#             */
/*   Updated: 2023/12/11 21:53:08 by senyilma         ###   ########.fr       */
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
		*lexer = free_null(*lexer);
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
		(*expander)->content = free_null((*expander)->content);
		if ((*expander)->ex_content)
			free((*expander)->ex_content);
		*expander = free_null(*expander);
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
	(*parser)->file = free_null((*parser)->file);
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
		(*parser)->command = free_null((*parser)->command);
		i = -1;
		while ((*parser)->parameters && (*parser)->parameters[++i])
			free((*parser)->parameters[i]);
		free ((*parser)->parameters);
		if ((*parser)->heredoc)
			(*parser)->heredoc = free_null((*parser)->heredoc);
		if ((*parser)->file)
			free_file(parser);
		*parser = free_null(*parser);
		*parser = temp;
	}
}

void	free_prime(t_prime *g_prime)
{
	int	i;

	free_lexer(&g_prime->lexer);
	free_expander(&g_prime->expander);
	free_parser(&g_prime->parser);
	g_prime->line = free_null(g_prime->line);
	g_prime->line = NULL;
	i = 0;
	while (i < g_prime->cmd_count - 1)
	{
		if (g_prime->fd && g_prime->fd[i])
			free(g_prime->fd[i]);
		i++;
	}
	if (g_prime->fd)
		free(g_prime->fd);
}
