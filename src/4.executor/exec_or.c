/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_or.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:10:28 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/20 14:23:07 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief This function executes the or command
 * @param bin the command to be executed
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/06/03
*/

#include "minishell.h"

int	exec_or(t_bin *bin, t_data **data)
{
	int		status;

	status = exec_tree(bin->left, data);
	if (status != 0)
		status = exec_tree(bin->right, data);
	return (status);
}
