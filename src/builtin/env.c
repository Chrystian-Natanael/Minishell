/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:36:33 by krocha-h          #+#    #+#             */
/*   Updated: 2024/06/01 21:15:44 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file pwd.c
 * @brief This file contains the pwd function
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/06/01
*/

#include "minishell.h"

int ft_env(char **argv, t_envp *envp)
{
	if (argv[1])
	{
		ft_putstr_fd("env: \'", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd("\': No such file or directory\n", 2);
		return (127);
	}
	while (envp)
	{
		ft_putstr_fd(envp->key, 1);
		ft_putstr_fd(envp->value, 1);
		ft_putchar_fd('\n', 1);
		envp = envp->next;
	}
	return (0);
}