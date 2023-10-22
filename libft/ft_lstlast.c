/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 03:46:04 by senyilma          #+#    #+#             */
/*   Updated: 2022/12/23 19:15:12 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list	*lst)
{
	t_list *temp;

	if (!lst)
		return (0);
	temp = lst;
	while (temp -> next != 0)
	{
		temp = temp -> next;
	}
	return (temp);
}
