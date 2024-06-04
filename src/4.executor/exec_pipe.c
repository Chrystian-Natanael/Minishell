/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:04:31 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/03 14:05:35 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function executes the pipe command
 * @param cmd the command to be executed
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/06/03
*/

int	exec_pipe(t_bin *bin, t_envp **envp)
{
	int		status;
	int		pipe_fd[2];
	int		old_fd[2];

	old_fd[0] = dup(STDIN_FILENO);
	old_fd[1] = dup(STDOUT_FILENO);
	if (pipe(pipe_fd) == -1)
		return (-1);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	status = exec_tree(bin->left, envp);
	dup2(old_fd[1], STDOUT_FILENO);
	close(old_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	status = exec_tree(bin->right, envp);
	dup2(old_fd[0], STDIN_FILENO);
	close(old_fd[0]);
	return (status);
}