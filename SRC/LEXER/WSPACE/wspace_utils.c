/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wspace_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 22:37:34 by senyilma          #+#    #+#             */
/*   Updated: 2023/11/01 02:11:43 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

int	chrchr_wspace(char c)
{
	return (c == 9 || c == 10 || c == 13 || c == 32);
}

int	strchr_wspace(char *str)
{
	if (ft_strchr(str, 9))
		return (9);
	if (ft_strchr(str, 10))
		return (10);
	if (ft_strchr(str, 13))
		return (13);
	if (ft_strchr(str, 32))
		return (32);
	return (0);
}
