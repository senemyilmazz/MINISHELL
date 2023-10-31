/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 22:35:16 by senyilma          #+#    #+#             */
/*   Updated: 2023/11/01 01:55:43 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

int	synerr_print(char *str)
{
	printf("%s", str);
	return (-1);
}

int	syn_error(int temp_type, int temp_len)
{
	if (temp_type == -1)
		return (synerr_print(SYN_PP));
	else if (temp_type == -2 && temp_len == 3)
		return (synerr_print(SYN_B));
	else if (temp_type == -2 && temp_len > 3)
		return (synerr_print(SYN_BB));
	else if (temp_type == -3 && temp_len == 4)
		return (synerr_print(SYN_M));
	else if (temp_type == -3 && temp_len == 5)
		return (synerr_print(SYN_MM));
	else if (temp_type == -3 && temp_len > 5)
		return (synerr_print(SYN_MMM));
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
			return (syn_error(t, ft_strlen(temp->content)));
		else if (g_prime->lexer->type == 1 || \
			(temp->next && temp->next->type == 1 && t > 0) || \
			(temp->type == 1 && !temp->next))
			return (synerr_print(SYN_P));
		else if ((t >= 2 && t <= 6) && (!temp->next || temp->next->type != 0))
			flag = 2;
		temp = temp->next;
	}
	if (flag == 2)
		return (synerr_print(SYN_NL));
	return (0);
}
