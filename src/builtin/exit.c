/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 20:05:19 by krocha-h          #+#    #+#             */
/*   Updated: 2024/06/01 21:22:39 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file pwd.c
 * @brief This file contains the pwd function
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/06/01
*/

#include "minishell.h"

int	ft_exit(char **argv)
{
	int	count;

	count = args_count(argv);
	if (!ft_isalnum(argv[1]))
	{
		ft_putstr_fd("-minishell: exit: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": numeric argument required", 2);
		quit(2);
	}
	else if (count > 2)
	{
		ft_putstr_fd("-minishell: exit: too many arguments\n", 2);
		return (1);		
	}
	else if (count == 2 && ft_isalnum(argv[1]))
		quit(ft_atoi(argv[1]));
	else
		quit(0);
}