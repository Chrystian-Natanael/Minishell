/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 14:16:42 by krocha-h          #+#    #+#             */
/*   Updated: 2024/06/01 14:51:13 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file pwd.c
 * @brief This file contains the pwd function
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/06/01
*/

#include "minishell.h"

int	args_count(char **argv)
{
	int	count;

	count =0;
	while (argv[count])
		count++;
	return (count);
}

int	echo(char **argv)
{
	int	i;
	int	count;
	int	n;

	i = 1;
	count = args_count(argv);
	if (count > 1)
	{
		if (ft_strncmp(argv[i], '-n', 2) == 0)
		{
			n = 1;
			i++;
		}
		while (argv[i])
		{
			ft_putstr_fd(argv[i], 1);
			if (argv[i + 1] && argv[i][0] != '\0')
				write(1, ' ', 1);
			i++;
		}
		if(n == 1)
			return (SUCCESS);
	}
	write(1, '\n', 1);
	return (SUCCESS);
}
