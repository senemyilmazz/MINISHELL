/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 03:46:07 by senyilma          #+#    #+#             */
/*   Updated: 2023/11/01 02:11:04 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list	*lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp;
	t_list	*a;

	temp = 0;
	if (!del || !lst || !f)
		return (0);
	temp = 0;
	while (lst != 0)
	{
		a = ft_lstnew(f(lst->content));
		if (!a)
			ft_lstclear(&a, del);
		ft_lstadd_back(&temp, a);
		lst = lst->next;
	}
	return (temp);
}
