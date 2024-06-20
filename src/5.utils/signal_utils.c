/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:46:38 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/20 19:47:07 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file signal_utils.c
 * @brief This file contains the signal functions
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/06/20
*/

#include "minishell.h"

int	term_by_signal(int status)
{
	return (((signed char)((status & 0x7f) + 1) >> 1) > 0);
}

int	term_normaly(int status)
{
	return (term_by_signal(status) == 0);
}

int	exit_status(int status)
{
	return ((status >> 8) & 0xFF);
}

int	term_signal(int status)
{
	return (status & 0x7F);
}

int	get_return_value(int status)
{
	if (term_by_signal(status))
	{
		if (term_signal(status) == SIGQUIT)
			ft_putendl_fd("QUIT" " (core dumped)", STDERR_FILENO);
		return (term_signal(status) + 128);
	}
	return (exit_status(status));
}
