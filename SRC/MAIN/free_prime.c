/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_prime.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 22:08:33 by senyilma          #+#    #+#             */
/*   Updated: 2023/11/07 18:42:44 by senyilma         ###   ########.fr       */
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
	//free(lexer);
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
	//free(lexer);
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
	//free_env_l(&g_prime->env_l);
	free(g_prime->line);
}
