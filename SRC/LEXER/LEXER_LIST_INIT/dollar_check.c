/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 23:01:24 by senyilma          #+#    #+#             */
/*   Updated: 2023/10/27 04:38:05 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDE/minishell.h"

t_lexer	*dollar_split(char *content)
{
	t_lexer	*temp;
	int		start;
	int		end;
	int		expand;

	end = 0;
	expand = 0;
	while (content[end])
	{
		start = end;
		if (content[start] != '$')
		{
			while (content[end] && content[end] != '$'
				&& content[end] != ' ')
				end++;
		}
		else
		{
			end++;
			expand = 1;
			while (content[end] && content[end] != '$'
				&& content[end] != ' ')
				end++;
		}
		lexer_add_node(&temp, ft_substr(content, start, end - start), 0, expand);
	}
	return (temp);
}

void	dollar_check(void)
{
	t_lexer	*pre_temp;
	t_lexer	*temp;
	t_lexer	*new;
	t_lexer	*old;

	pre_temp = g_prime.lexer;
	temp = pre_temp;
	//while (pre_temp->next)
	//{
	while (temp)
	{
		if (temp->expand == 1)
		{
			new = dollar_split(temp->content);
			if (temp == g_prime.lexer)
			{
				temp = temp->next;
				g_prime.lexer = new;
				new->next = temp;
			}
			else
			{
				while (pre_temp->next != temp)
					pre_temp = pre_temp->next;
				pre_temp->next = new;
				if (temp->next)
				{
					new->next = temp->next;
					while ()
					temp = ;
				}
				else if (temp->next == NULL)
				{
					
				}
				free(temp);
			}
			
		}
		temp = temp->next;
		pre_temp = temp;
	}
	//}
}