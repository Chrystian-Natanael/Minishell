/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:44:27 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/03 07:59:21 by cnatanae         ###   ########.fr       */
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
	// int		pid;
	int		exit_status;
	char	**cmd;
	// char	*path_cmd;
	// char	**envp_export;

	// envp_export = NULL;
	cmd = ft_split(bin->cmd, ' ');
	typetree_insert(cmd);
	typetree_insert_matrix((void **)cmd);
	exit_status = check_exec_builtin(cmd, envp);
	if (exit_status != -1)
		return (exit_status);
	// pid = fork();
	// if (pid == -1)
	// {
	// 	return (-1);
	// }
	// exit_status = 0;
	// if (cmd[0] == NULL)
	// 	return (-1);
	// path_cmd = get_path_cmd(cmd[0], envp_export);
	// if (pid == 0){
	// 	execve(path_cmd, cmd, envp_export);
	// 	if (access(path_cmd, F_OK) != 0)
	// 	{
	// 		exit_status = 127;
	// 	}
	// 	else if (access(path_cmd, X_OK | F_OK) != 0)
	// 	{
	// 		exit_status = 126;
	// 	}
	// 	exit_status = (exit_status >> 8) & 0xFF;
	// }
	// waitpid(pid, NULL, 0);
	return (exit_status);
}


// int	exec_or(t_bin *bin, t_envp *envp)
// {
// 	int	status;

// 	status = exec_cmd(bin->left, envp);
// 	if (status != 0)
// 		status = exec_cmd(bin->right, envp);
// 	return (status);
// }

// int	exec_and(t_bin *bin, t_envp *envp)
// {
// 	int	status;

// 	status = exec_cmd(bin->left, envp);
// 	if (status == 0)
// 		status = exec_cmd(bin->right, envp);
// 	return (status);
// }

int	exec_tree(t_bin *bin, t_envp **envp)
{
	if (bin->type == CMD)
		return (exec_cmd(bin, envp));
	// else if (bin->type == AND)
	// 	return (exec_and(bin, envp));
	// else if (bin->type == OR)
	// 	return (exec_or(bin, envp));
	// else if (bin->type == PIPE)
	// 	return (exec_pipe(bin, envp));
	// else if (bin->type == REDIR_INPUT)
	// 	return (exec_redir_input(bin, envp));
	// else if (bin->type == REDIR_OUTPUT)
	// 	return (exec_redir_output(bin, envp));
	// else if (bin->type == OUTPUT_APPEND)
	// 	return (exec_output_append(bin, envp));
	// else if (bin->type == HEREDOC)
	// 	return (exec_heredoc(bin, envp));
	// else if (bin->type == SUB_SHELL)
	// 	return (exec_sub_shell(bin, envp));
	else
		return (-1);
}

//-------------considera a lista de variáveis de ambiente
void	execute(t_token *tokens, t_envp **envp)
{
	int		status;
	t_bin	*bin;

	bin = create_tree(tokens);
	status = exec_tree(bin, envp);
	(void)status;
}