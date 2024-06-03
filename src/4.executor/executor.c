/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:44:27 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/03 10:54:00 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file executor.c
 * @brief This file contains the executor functions
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/05/06
*/

#include "minishell.h"

int	exec_cmd(t_bin *bin, t_envp **envp, t_fd *fd)
{
	int		pid;
	int		exit_status;
	char	**cmd;
	char	*path;

	cmd = ft_split(bin->cmd, ' ');
	typetree_insert(cmd);
	typetree_insert_matrix((void **)cmd);
	exit_status = check_exec_builtin(cmd, envp, fd);
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
			exit_status = 127;
		else if (access(path, X_OK | F_OK) != 0)
			exit_status = 126;
		exit_status = (exit_status >> 8) & 0xFF;
	}
	waitpid(pid, NULL, 0);
	return (exit_status);
}

char	**t_envp_to_char(t_envp **envp)
{
	t_envp	*curr;
	char	**envp_char;
	int		i;

	i = size_envp(envp);
	envp_char = allocate(sizeof(char *) * (i + 1));
	if (!envp_char)
		return (NULL);
	i = 0;
	curr = *envp;
	while (curr)
	{
		envp_char[i] = ft_strjoin(curr->key, "=");
		envp_char[i] = ft_strjoin(envp_char[i], curr->value);
		i++;
		curr = curr->next;
	}
	envp_char[i] = NULL;
	return (envp_char);
}

int	size_envp(t_envp **envp)
{
	t_envp	*curr;
	int		i;

	i = 0;
	curr = *envp;
	while (curr)
	{
		i++;
		curr = curr->next;
	}
	return (i);
}

char	*get_path_cmd(t_envp **envp, char *cmd)
{
	t_envp	*curr;
	char	*path;
	char	**split;
	curr = *envp;
	while (curr)
	{
		if (ft_strncmp(curr->key, "PATH", 4) == 0)
		{
			split = ft_split(curr->value, ':');
			typetree_insert_matrix((void **)split);
			typetree_insert(split);
			while (*split)
			{
				path = ft_strjoin(*split, "/");
				typetree_insert(path);
				path = ft_strjoin(path, cmd);
				typetree_insert(path);
				if (access(path, F_OK) == 0)
					return (path);
				split++;
			}
			return (path);
		}
		curr = curr->next;
	}
	return (NULL);
}

int	exec_tree(t_bin *bin, t_envp **envp, t_fd *fd)
{
	if (bin->type == CMD)
		return (exec_cmd(bin, envp, fd));
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

void	execute(t_token *tokens, t_envp **envp)
{
	int		status;
	t_bin	*bin;
	t_fd	fd;

	fd.fd_in = 0;
	fd.fd_out = 1;
	bin = create_tree(tokens);
	status = exec_tree(bin, envp, &fd);
	(void)status;
}