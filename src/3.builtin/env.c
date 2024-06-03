/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:36:33 by krocha-h          #+#    #+#             */
/*   Updated: 2024/06/03 13:33:05 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file env.c
 * @brief This file contains the env function
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/06/01
*/

#include "minishell.h"

int	ft_env(char **argv, t_envp **envp)
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
		ft_putstr_fd(curr->key, STDOUT_FILENO);
		ft_putchar_fd('=', STDOUT_FILENO);
		ft_putstr_fd(curr->value, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		curr = curr->next;
	}
	return (0);
}
