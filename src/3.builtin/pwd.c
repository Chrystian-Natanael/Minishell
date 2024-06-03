/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 12:15:35 by krocha-h          #+#    #+#             */
/*   Updated: 2024/06/03 10:14:38 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file pwd.c
 * @brief This file contains the pwd function
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/05/31
*/

#include "minishell.h"

int	ft_pwd(t_fd *fd)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
	{
		ft_putstr_fd(cwd, fd->fd_out);
		ft_putchar_fd('\n', fd->fd_out);
	}
	return (0);
}
