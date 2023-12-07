/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 22:35:16 by senyilma          #+#    #+#             */
/*   Updated: 2023/12/07 17:32:35 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

int	syn_error(t_prime *g_prime, int temp_type, int temp_len)
{
	if (temp_type == -1)
		return (synerr_print(g_prime, "||", 0));
	else if (temp_type == -2 && temp_len == 3)
		return (synerr_print(g_prime, ">", 0));
	else if (temp_type == -2 && temp_len > 3)
		return (synerr_print(g_prime, ">>", 0));
	else if (temp_type == -3 && temp_len == 3)
		return (synerr_print(g_prime, "<", 0));
	else if (temp_type == -3 && temp_len < 5)
		return (synerr_print(g_prime, "<<", 0));
	else if (temp_type == -3 && temp_len > 5)
		return (synerr_print(g_prime, "<<<", 0));
	return (0);
}

int	syntax_check(t_prime *g_prime)
{
	t_lexer	*temp;
	int		flag;
	int		t;

	temp = g_prime->lexer;
	type_init(g_prime);
	flag = 0;
	while (temp)
	{
		t = temp->type;
		if (t == -1 || t == -2 || t == -3)
			return (syn_error(g_prime, t, ft_strlen(temp->content)));
		else if (g_prime->lexer->type == SIGN_PIPE || \
			(temp->next && temp->next->type == SIGN_PIPE && t > 0) || \
			(temp->type == SIGN_PIPE && !temp->next))
			return (synerr_print(g_prime, "|", 0));
		else if ((t >= SIGN_SOR && t <= 5) && (!temp->next || temp->next->type))
			flag = 2;
		temp = temp->next;
	}
	if (flag == 2)
		return (synerr_print(g_prime, "newline", 0));
	return (0);
}
