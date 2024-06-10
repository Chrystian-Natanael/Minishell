/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:09:18 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/10 12:49:48 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function executes the and command
 * @param bin the command to be executed
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/06/03
*/

int	exec_and(t_bin *bin, t_envp **envp, t_data *data)
{
	int		status;

	status = exec_tree(bin->left, envp, data);
	if (status == 0)
		status = exec_tree(bin->right, envp, data);
	return (status);
}
