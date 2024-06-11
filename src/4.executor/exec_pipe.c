/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:04:31 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/11 07:32:18 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function executes the pipe command
 * @param cmd the command to be executed
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/06/03
*/

int	exec_pipe(t_bin *bin, t_data **data)
{
	int		status;
	int		pipe_fd[2];
	int		old_fd[2];
	int		pid[2];

	old_fd[0] = dup(STDIN_FILENO);
	old_fd[1] = dup(STDOUT_FILENO);
	if (pipe(pipe_fd) == -1)
		return (-1);
	pid[0] = fork();
	if (pid[0] == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		close(old_fd[0]);
		close(old_fd[1]);
		ending(exec_tree(bin->left, data), *data);
	}
	close(pipe_fd[1]);
	pid[1] = fork();
	if (pid[1] == 0)
	{
		close(old_fd[1]);
		close(old_fd[0]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		ending(exec_tree(bin->right, data), *data);
	}
	close(pipe_fd[0]);
	dup2(old_fd[1], STDOUT_FILENO);
	close(old_fd[1]);
	dup2(old_fd[0], STDIN_FILENO);
	close(old_fd[0]);
	waitpid(pid[0], &status, 0);
	waitpid(pid[1], &status, 0);
	return ((status >> 8) & 0xFF);
}
