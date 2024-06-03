/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:36:33 by krocha-h          #+#    #+#             */
/*   Updated: 2024/06/03 10:13:12 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file env.c
 * @brief This file contains the env function
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/06/01
*/

#include "minishell.h"

int	ft_env(char **argv, t_envp **envp, t_fd *fd)
{
	t_envp	*curr;

	curr = *envp;
	if (argv[1])
	{
		return (ft_error("minishell: env: \'", \
		argv[1], "\': No such file or directory\n", 127));
	}
	while (curr)
	{
		ft_putstr_fd(curr->key, fd->fd_out);
		ft_putchar_fd('=', fd->fd_out);
		ft_putstr_fd(curr->value, fd->fd_out);
		ft_putchar_fd('\n', fd->fd_out);
		curr = curr->next;
	}
	return (0);
}
