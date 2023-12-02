/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 22:35:16 by senyilma          #+#    #+#             */
/*   Updated: 2023/12/02 14:14:30 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

int	synerr_print(t_prime *g_prime, char *str)
{
	printf("bash: syntax error near unexpected token '%s'\n", str);
	g_prime->exit_code = 258;
	return (-1);
}

int	syn_error(t_prime *g_prime, int temp_type, int temp_len)
{
	if (temp_type == -1)
		return (synerr_print(g_prime, "||"));
	else if (temp_type == -2 && temp_len == 3)
		return (synerr_print(g_prime, ">"));
	else if (temp_type == -2 && temp_len > 3)
		return (synerr_print(g_prime, ">>"));
	else if (temp_type == -3 && temp_len == 3)
		return (synerr_print(g_prime, "<"));
	else if (temp_type == -3 && temp_len < 5)
		return (synerr_print(g_prime, "<<"));
	else if (temp_type == -3 && temp_len > 5)
		return (synerr_print(g_prime, "<<<"));
	return (0);
}

int	syntax_check(t_prime *g_prime)
{
	t_lexer	*temp;
	int		flag;
	int		t;

	temp = g_prime->lexer;
	type_check(g_prime);
	flag = 0;
	while (temp)
	{
		t = temp->type;
		if (t == -1 || t == -2 || t == -3)
			return (syn_error(g_prime, t, ft_strlen(temp->content)));
		else if (g_prime->lexer->type == SIGN_PIPE || \
			(temp->next && temp->next->type == SIGN_PIPE && t > 0) || \
			(temp->type == SIGN_PIPE && !temp->next))
			return (synerr_print(g_prime, "|"));
		else if ((t >= SIGN_SOR && t <= 5) && (!temp->next || temp->next->type))
			flag = 2;
		temp = temp->next;
	}
	if (flag == 2)
		return (synerr_print(g_prime, "newline"));
	return (0);
}
