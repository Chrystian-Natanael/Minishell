/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 10:58:04 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/18 15:50:47 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function executes the redirection input command
 * @param bin the command to be executed
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/06/07
*/

int	exec_redir_input(t_bin *bin, t_data **data)
{
	int		fd;
	int		status;
	int		std_in;

	std_in = dup(STDIN_FILENO);
	fd = open(bin->right->cmd, O_RDONLY);
	if (fd == -1)
		return (ft_error("minishell: ", bin->right->cmd, \
		": No such file or directory", 1));
	dup2(fd, STDIN_FILENO);
	close(fd);
	if (bin->left)
		status = exec_tree(bin->left, data);
	else if (bin->right->left)
		status = exec_tree(bin->right->left, data);
	else if (bin->right->right)
		status = exec_tree(bin->right->right, data);
	else
		status = -1;
	dup2(std_in, STDIN_FILENO);
	close(std_in);
	return (status);
}
