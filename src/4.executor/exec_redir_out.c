/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_out.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 10:30:37 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/11 07:26:15 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function executes the redirection output command
 * @param bin the command to be executed
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/06/07
*/

int	exec_redir_out(t_bin *bin, t_data **data)
{
	if (bin->type == REDIR_OUTPUT)
		return (exec_redir_output(bin, data));
	else
		return (exec_redir_append(bin, data));
}

int	exec_redir_output(t_bin *bin, t_data **data)
{
	int		fd;
	int		status;
	int		std_out;

	std_out = dup(STDOUT_FILENO);
	fd = open(bin->right->cmd, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		return (ft_error("minishell: %s: \n", bin->right->cmd, \
		"No such file or directory", 1));
	dup2(fd, STDOUT_FILENO);
	close(fd);
	status = exec_tree(bin->left, data);
	dup2(std_out, STDOUT_FILENO);
	close(std_out);
	return (status);
}

int	exec_redir_append(t_bin *bin, t_data **data)
{
	int		fd;
	int		status;
	int		std_out;

	std_out = dup(STDOUT_FILENO);
	fd = open(bin->right->cmd, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
		return (ft_error("minishell: %s: \n", bin->right->cmd, \
		"No such file or directory", 1));
	dup2(fd, STDOUT_FILENO);
	close(fd);
	status = exec_tree(bin->left, data);
	dup2(std_out, STDOUT_FILENO);
	close(std_out);
	return (status);
}
