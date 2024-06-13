/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 18:03:49 by krocha-h          #+#    #+#             */
/*   Updated: 2024/06/13 19:26:09 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file signals.c
 * @brief This file contains the main function
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/04/08
*/

#include "minishell.h"

void	change_global(int sig)
{
	g_sign = sig;
	rl_on_new_line();
	rl_replace_line("", 0);
	close(STDIN_FILENO);
}

void	heredoc_signals(void)
{
	signal(SIGINT, change_global);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
}

void	line_feed(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 1);
}

void	sig_handler(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	define_signals_exec(int pid)
{
	if (pid == 0)
		signal(SIGINT, SIG_DFL);
	else
		signal(SIGINT, line_feed);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
}


void	init_signals(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
}
