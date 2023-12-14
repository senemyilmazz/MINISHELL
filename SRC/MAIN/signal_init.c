/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 00:57:01 by senyilma          #+#    #+#             */
/*   Updated: 2023/12/11 17:46:29 by senyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDE/minishell.h"

static void	ft_termios(void)
{
	struct termios	termios_p;

	if (tcgetattr(0, &termios_p) != 0)
		perror("Minishell: tcgetattr");
	termios_p.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, 0, &termios_p) != 0)
		perror("Minishell: tcsetattr");
}

void	interrupt_here_document(int signal)
{
	(void)signal;
	exit(1);
}

static void	signal_handler(int sig)
{
	if (sig == SIGINT && g_signal == 2)
	{
		rl_redisplay();
		g_signal = 1;
	}
	else if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_signal = 1;
	}
	else if (sig == SIGQUIT)
	{
		rl_redisplay();
	}
}

void	signal_init(void)
{
	ft_termios();
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	signal(EOF, signal_handler);
}
