/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:44:27 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/04 08:13:33 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file executor.c
 * @brief This file contains the executor functions
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/05/06
*/

#include "minishell.h"

int	exec_cmd(t_bin *bin, t_envp **envp)
{
	int		pid;
	int		exit_status;
	char	**cmd;
	char	*path;

	cmd = ft_split(bin->cmd, ' ');
	typetree_insert(cmd);
	typetree_insert_matrix((void **)cmd);
	exit_status = check_exec_builtin(cmd, envp);
	if (exit_status != -1)
		return (exit_status);
	pid = fork();
	if (pid == -1 || cmd[0] == NULL)
		return (-1);
	exit_status = 0;
	path = get_path_cmd(envp, cmd[0]);
	if (pid == 0)
	{
		execve(path, cmd, t_envp_to_char(envp));
		if (access(path, F_OK) != 0)
		{
			ft_printf("minishell: %s: command not found\n", cmd[0]);
			exit_status = 127;
		}
		else if (access(path, X_OK | F_OK) != 0)
			exit_status = 126;
		ending (exit_status);
	}
	waitpid(pid, &exit_status, 0);
	return ((exit_status >> 8) & 0xFF);
}

int	exec_tree(t_bin *bin, t_envp **envp)
{
	if (bin->type == CMD)					//! FINISH
		return (exec_cmd(bin, envp));
	else if (bin->type == AND)				//! FINISH
		return (exec_and(bin, envp));
	else if (bin->type == OR)				//! FINISH
		return (exec_or(bin, envp));
	else if (bin->type == PIPE)				//! FINISH
		return (exec_pipe(bin, envp));
	// else if (bin->type == REDIR_INPUT || bin->type == HEREDOC)
	// 	return (exec_redir_in(bin, envp));
	// else if (bin->type == REDIR_OUTPUT || bin->type == OUTPUT_APPEND)
	// 	return (exec_redir_out(bin, envp));
	else if (bin->type == SUB_SHELL)		//! FINISH (Mas falta fazer uns testes... XD)
		return (exec_sub_shell(bin, envp));
	else
		return (-1);
}

int	execute(t_token *tokens, t_envp **envp)
{
	int		status;
	t_bin	*bin;

	bin = create_tree(tokens);
	status = exec_tree(bin, envp);
	return (status);
}