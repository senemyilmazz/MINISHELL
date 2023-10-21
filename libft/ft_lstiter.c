/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 03:46:02 by senyilma          #+#    #+#             */
/*   Updated: 2022/12/27 14:05:31 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

void	ft_lstiter(t_list	*lst, void (*f)(void *))
{
	t_list	*iter;

	if (lst && f)
	{
		iter = lst;
		while (iter)
		{
			f(iter->content);
			iter = iter->next;
		}
	}
	return ;
}
