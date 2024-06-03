/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_or.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:10:28 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/03 14:10:47 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function executes the or command
 * @param bin the command to be executed
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/06/03
*/

int	exec_or(t_bin *bin, t_envp **envp)
{
	int		status;

	status = exec_tree(bin->left, envp);
	if (status != 0)
		status = exec_tree(bin->right, envp);
	return (status);
}
