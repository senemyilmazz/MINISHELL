/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: senyilma <senyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 00:57:01 by senyilma          #+#    #+#             */
/*   Updated: 2023/12/02 11:00:06 by senyilma         ###   ########.fr       */
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

void	signal_handler(int sig)
{
	(void)sig;
	if (sig == SIGINT)
	{
		printf("sigint\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		//130 koduyla çıkacak!!;
	}
	else if (sig == EOF)
	{
		printf("eof\n");
		rl_on_new_line();
		//rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		printf("sigquit\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/*void	ft_handler(int sig)
{
	//if (g_global.test1)
	//{
	//	close_heredoc(sig);
	//	return ;
	//}
	//else
	//{
		//if (g_global.test2)
		//{
			ft_putstr_fd("\n", 2);
			rl_on_new_line();
			rl_replace_line("", 0);
			return ;
		//}
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		write(1, "\033[A", 3);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	//}
}*/

void	init_signal(void)
{
	ft_termios();
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	signal(EOF, signal_handler);
}
