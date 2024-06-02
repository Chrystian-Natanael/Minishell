/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 20:05:19 by krocha-h          #+#    #+#             */
/*   Updated: 2024/06/02 19:40:14 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file exit.c
 * @brief This file contains the exit function
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/06/01
*/

#include "minishell.h"

int	ft_exit(char **argv)
{
	int	count;

	count = args_count(argv);
	if (!ft_isonlynum(argv[1]))
	{
		ft_putstr_fd("-minishell: exit: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		quit(2);
	}
	else if (count > 2)
	{
		ft_putstr_fd("-minishell: exit: too many arguments\n", 2);
		return (1);
	}
	else if (count == 2 && ft_isonlynum(argv[1]))
		quit(ft_atoi(argv[1]));
	else
		quit(0);
	return (0);
}
