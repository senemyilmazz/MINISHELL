/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 23:01:38 by mkati             #+#    #+#             */
/*   Updated: 2023/12/05 02:08:46 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../INCLUDE/minishell.h"

void	interrupt_here_document(int signal)
{
	(void)signal;
	g_signal = 2;
	exit(1);
}

static void	heredoc_read(t_parser *parser, char *end, int *fd)
{
	char	*str;

	str = 0;
	if (parser->heredoc)
		free(parser->heredoc);
	parser->heredoc = 0;
	signal(SIGINT, interrupt_here_document);
	while (1)
	{
		str = readline("> ");
		if (str == NULL || g_signal == 2 || strcmp(str, end) == 0)
		{
			free(str);
			break ;
		}
		parser->heredoc = ft_strjoin(parser->heredoc, str);
		parser->heredoc = ft_strjoin(parser->heredoc, "\n");
		free(str);
	}
	write(fd[1], parser->heredoc, strlen(parser->heredoc));
}

void	heredoc_init(t_prime *g_prime)
{
	t_expander	*temp_ex;
	t_parser	*temp_parser;
	int			fd[2];
	int			pid;

	temp_ex = g_prime->expander;
	temp_parser = g_prime->parser;
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		signal(SIGINT, interrupt_here_document);
		while (temp_ex)
		{
			while (temp_ex && temp_ex->type != 1)
			{
				if (temp_ex->type == HEREDOC)
					heredoc_read(temp_parser, temp_ex->next->content, fd);
				temp_ex = temp_ex->next;
			}
			if (temp_ex)
				temp_ex = temp_ex->next;
			temp_parser = temp_parser->next;
		}
		close(fd[1]);
		exit(0);
	}

	close(fd[1]);
	waitpid(pid, NULL, 0);

	char buffer[100];
	ssize_t bytesRead = read(fd[0], buffer, sizeof(buffer) - 1);
	buffer[bytesRead] = '\0';
	temp_parser->heredoc = malloc(strlen(buffer) + 1);
	if (temp_parser->heredoc == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	strcpy(temp_parser->heredoc, buffer);
	close(fd[0]);
}