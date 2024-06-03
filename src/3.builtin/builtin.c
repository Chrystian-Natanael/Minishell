/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:14:29 by krocha-h          #+#    #+#             */
/*   Updated: 2024/06/03 13:32:20 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file builtin.c
 * @brief This file contains the function that execute builtin
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/06/02
*/

#include "minishell.h"

int	check_exec_builtin(char **cmd, t_envp **envp)
{
	if (ft_strcmp(cmd[0], "echo") == 0)
		return (ft_echo(cmd));
	if (ft_strcmp(cmd[0], "env") == 0)
		return (ft_env(cmd, envp));
	if (ft_strcmp(cmd[0], "exit") == 0)
		return (ft_exit(cmd));
	if (ft_strcmp(cmd[0], "export") == 0)
		return (ft_export(cmd, envp));
	if (ft_strcmp(cmd[0], "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(cmd[0], "unset") == 0)
		return (ft_unset(cmd, envp));
	// if (ft_strcmp(cmd[0], "cd") == 0)
	// 	return (ft_cd(cmd));
	return (-1);
}