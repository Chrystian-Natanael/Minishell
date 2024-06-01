/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 12:15:35 by krocha-h          #+#    #+#             */
/*   Updated: 2024/05/31 12:28:37 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file pwd.c
 * @brief This file contains the pwd function
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/05/31
*/

#include "minishell.h"

int	pwd(void)
{
	char	cwd[PATH_MAX];
	
	getcwd(cwd, PATH_MAX);
	if (cwd)
	{
		ft_putstr_fd(cwd, 1);
		return (SUCCESS);
	}
	return (FAILURE);
}
