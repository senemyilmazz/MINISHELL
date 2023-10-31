/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 03:45:49 by senyilma          #+#    #+#             */
/*   Updated: 2023/10/31 21:22:20 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list	**lst, t_list	*new)
{
	if (new)
	{
		if (!*lst)
		{
			*lst = new;
			return ;
		}
		ft_lstlast(*lst)->next = new;
		new->next = 0;
	}
}
