/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:44:27 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/19 15:44:21 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file executor.c
 * @brief This file contains the executor functions
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/05/06
*/

#include "minishell.h"

void	exec_init(char ***cmd, int *exit_status, t_bin *bin, t_data **data)
{
	*cmd = ft_split(bin->cmd, ' ');
	typetree_insert(*cmd);
	typetree_insert_matrix((void **)(*cmd));
	*exit_status = check_exec_builtin(*cmd, &(*data)->my_envp, *data);
}

int	exec_cmd(t_bin *bin, t_data **data)
{
	int		pid;
	int		exit_status;
	char	**cmd;
	char	*path;
	char	**envp;

	exec_init(&cmd, &exit_status, bin, data);
	if (exit_status != -1)
		return (exit_status);
	pid = fork();
	define_signals_exec(pid);
	if (pid == -1 || cmd[0] == NULL)
		return (-1);
	exit_status = 0;
	path = get_path_cmd(&(*data)->my_envp, cmd[0]);
	if (pid == 0)
	{
		envp = create_envp_array(&(*data)->my_envp);
		execve(path, cmd, envp);
		if (access(cmd[0], F_OK) != 0 || ft_strchr(cmd[0], '/') == NULL)
			exit_status = ft_error("minishell: ", cmd[0], \
			": command not found", 127);
		else
			exit_status = 126;
		free_split(envp);
		ending (exit_status, *data);
	}
	waitpid(pid, &exit_status, 0);
	return ((exit_status >> 8) & 0xFF);
}

int	exec_tree(t_bin *bin, t_data **data)
{
	if (bin->type == CMD)
		return (exec_cmd(bin, data));
	else if (bin->type == AND)
		return (exec_and(bin, data));
	else if (bin->type == OR)
		return (exec_or(bin, data));
	else if (bin->type == PIPE)
		return (exec_pipe(bin, data));
	else if (bin->type == REDIR_INPUT)
		return (exec_redir_input(bin, data));
	else if (bin->type == REDIR_OUTPUT || bin->type == OUTPUT_APPEND)
		return (exec_redir_out(bin, data));
	else if (bin->type == SUB_SHELL)
		return (exec_sub_shell(bin, data));
	else
		return (-1);
}

int	execute(t_token *tokens, t_data *data)
{
	int		status;
	t_bin	*bin;

	bin = create_tree(tokens);
	status = exec_tree(bin, &data);
	return (status);
}
