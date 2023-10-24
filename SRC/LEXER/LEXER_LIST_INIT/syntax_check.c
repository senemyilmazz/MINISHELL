/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 07:20:14 by senyilma          #+#    #+#             */
/*   Updated: 2023/10/24 16:18:21 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

void	type_match(t_lexer *temp)
{
	if (temp->type == 3 && ft_strlen(temp->content) == 2)
		temp->type = 4;
	else if (temp->type == 2 && ft_strlen(temp->content) == 2)
		temp->type = 5;
	else if (temp->type == 3 && ft_strlen(temp->content) == 3)
		temp->type = 6;
	else if (temp->type == 1 && ft_strlen(temp->content) > 1)
		temp->type = -1;
	else if (temp->type == 2 && ft_strlen(temp->content) > 2)
		temp->type = -2;
	else if (temp->type == 3 && ft_strlen(temp->content) > 3)
		temp->type = -3;
}


void	type_check(void)
{
	t_lexer	*temp;

	temp = g_prime.lexer;
	while (temp)
	{
		if (temp->type != 0)
			type_match(temp);
		temp = temp->next;
	}
}

int	syntax_check(void)
{
	t_lexer	*temp;
	int		flag;

	type_check();
	temp = g_prime.lexer;
	flag = 0;
	while (temp)
	{
		if (temp->type == -1)
		{
			printf("bash: syntax error near unexpected token `||'\n");
			flag = 0;
			return (-1);
		}
		else if (temp->type == -2 && ft_strlen(temp->content) == 3)
		{
			printf("bash: syntax error near unexpected token `>'\n");
			flag = 0;
			return (-1);
		}
		else if (temp->type == -2 && ft_strlen(temp->content) > 3)
		{
			printf("bash: syntax error near unexpected token `>>'\n");
			flag = 0;
			return (-1);
		}
		else if (temp->type == -3 && ft_strlen(temp->content) == 4)
		{
			printf("bash: syntax error near unexpected token `<'\n");
			flag = 0;
			return (-1);
		}
		else if (temp->type == -3 && ft_strlen(temp->content) == 5)
		{
			printf("bash: syntax error near unexpected token `<<'\n");
			flag = 0;
			return (-1);
		}
		else if (temp->type == -3 && ft_strlen(temp->content) > 5)
		{
			printf("bash: syntax error near unexpected token `<<<'\n");
			flag = 0;
			return (-1);
		}
		else if (g_prime.lexer->type == 1 || \
			(temp->next && temp->next->type == 1 && temp->type > 0))
		{
			printf("bash: syntax error near unexpected token `|'\n");
			return (-1);
		}
		else if ((temp->type >= 2 && temp->type <= 6)
			&& (!temp->next || temp->next->type != 0))
			flag = 2;
		temp = temp->next;
	}
	if (flag == 2)
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		return (-1);
	}
	return (0);
}
