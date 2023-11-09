/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 20:58:02 by senyilma          #+#    #+#             */
/*   Updated: 2023/11/10 00:48:41 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDE/minishell.h"

void	print_parser(t_prime *g_prime)
{
	t_parser	*temp;
	int			i;

	temp = g_prime->parser;
	while (temp)
	{
		printf("------------------------------\n");
		printf("command: %s\n", temp->command);
		printf("path: ");
		i = -1;
		while (temp->parameters && temp->parameters[++i])
			printf(" %s ; ", temp->parameters[i]);
		printf("\ninfile: %d\n", temp->infile);
		printf("outfile: %d\n", temp->outfile);
		while (temp->file)
		{
			printf("{filename: %s ; re_type %d}", \
				temp->file->filename, temp->file->re_type);
			temp->file = temp->file->next;
		}
		i = -1;
		while (temp->heredoc && temp->heredoc[++i])
			printf("\nheredoc %d:\n%s", i, temp->heredoc[i]);
		printf("\n------------------------------\n");
		temp = temp->next;
	}
}
