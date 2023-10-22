/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 07:20:14 by senyilma          #+#    #+#             */
/*   Updated: 2023/10/21 07:36:22 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

void    type_match(t_lexer *temp)
{
    if (temp->type == 2 && ft_strlen(temp->content) == 2)
		temp->type = 4;
	else if (temp->type == 3 && ft_strlen(temp->content) == 2)
		temp->type = 5;
    else if (ft_strlen(temp->content) > 1)
		temp->type = -1;
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

int syntax_check(void)
{
    t_lexer *temp;
    t_lexer* temp2;

    temp = g_prime.lexer;
    type_check();
    while(temp)
    {
        if (temp->type == -1)
        {
            printf("bash: syntax error near unexpected token `%c'\n", *temp->content);
            return (-1);
        }
        if (temp->next)
        {
            temp2 = temp->next;
            if ((temp->type != 0  && temp->type != 1) && (temp2->type != 1 && temp2->type != 0))
               {
                    printf("bash: syntax error near unexpected token `%s'\n", temp2->content);
                    return (-1);
               }
        }
        temp = temp->next;
    }
    return (0);
}
