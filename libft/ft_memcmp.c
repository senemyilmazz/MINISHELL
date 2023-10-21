/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 03:46:25 by senyilma          #+#    #+#             */
/*   Updated: 2022/12/27 16:00:45 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*d1;
	unsigned char	*d2;

	d1 = (unsigned char *) s1;
	d2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while ((n - 1) > 0)
	{
		if (*d1 == *d2)
		{
			d1++;
			d2++;
		}
		else
			break ;
		n--;
	}
	return (*d1 - *d2);
}
