/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 14:16:42 by krocha-h          #+#    #+#             */
/*   Updated: 2024/06/02 18:19:39 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file echo.c
 * @brief This file contains the echo function
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/06/01
*/

#include "minishell.h"

int	ft_echo(char **argv)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	if (args_count(argv) > 1)
	{
		if (ft_strncmp(argv[i], "-n", 2) == 0)
		{
			n = 1;
			i++;
		}
		while (argv[i])
		{
			ft_putstr_fd(argv[i], 1);
			if (argv[i + 1] && argv[i][0] != '\0')
				ft_putchar_fd(' ', 1);
			i++;
		}
		if (n == 1)
			return (0);
	}
	ft_putchar_fd('\n', 1);
	return (0);
}
