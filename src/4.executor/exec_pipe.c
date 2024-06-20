/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:04:31 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/20 20:31:06 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief This function executes the pipe command
 * @param cmd the command to be executed
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/06/03
*/

#include "minishell.h"

void	child_one(int *pipe_fd, const int *old_fd, t_bin *bin, t_data **data)
{
	close(old_fd[1]);
	close(old_fd[0]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	ending(exec_tree(bin->right, data), *data);
}

void	child_zero(int *pipe_fd, const int *old_fd, t_bin *bin, t_data **data)
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
	int			status[2];
	int			pipe_fd[2];
	const int	old_fd[2] = {dup(STDIN_FILENO), dup(STDOUT_FILENO)};
	int			pid[2];

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
	close_dup_fd(&old_fd[1]);
	close_dup_fd(&old_fd[0]);
	waitpid(pid[0], &status[0], 0);
	waitpid(pid[1], &status[1], 0);
	if (g_sign == 0)
		return (get_return_value(status[1]));
	return (130);
}
