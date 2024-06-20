/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:04:31 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/20 17:25:59 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief This function executes the pipe command
 * @param cmd the command to be executed
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/06/03
*/

#include "minishell.h"

void	child_one(int *pipe_fd, int *old_fd, t_bin *bin, t_data **data)
{
	close(old_fd[1]);
	close(old_fd[0]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	ending(exec_tree(bin->right, data), *data);
}

void	child_zero(int *pipe_fd, int *old_fd, t_bin *bin, t_data **data)
{
	close(pipe_fd[0]);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	close(old_fd[0]);
	close(old_fd[1]);
	ending(exec_tree(bin->left, data), *data);
}

int	exec_pipe(t_bin *bin, t_data **data)
{
	int		status[2];
	int		pipe_fd[2];
	int		old_fd[2];
	int		pid[2];

	old_fd[0] = dup(STDIN_FILENO);
	old_fd[1] = dup(STDOUT_FILENO);
	if (pipe(pipe_fd) == -1)
		return (-1);
	pid[0] = fork();
	define_signals_exec(pid[0]);
	if (pid[0] == 0)
		child_zero(pipe_fd, old_fd, bin, data);
	close(pipe_fd[1]);
	pid[1] = fork();
	define_signals_exec(pid[1]);
	if (pid[1] == 0)
		child_one(pipe_fd, old_fd, bin, data);
	close(pipe_fd[0]);
	dup2(old_fd[1], STDOUT_FILENO);
	close(old_fd[1]);
	dup2(old_fd[0], STDIN_FILENO);
	close(old_fd[0]);
	waitpid(pid[0], &status[0], 0);
	waitpid(pid[1], &status[1], 0);
	return ((status[1] >> 8) & 0xFF);
}
