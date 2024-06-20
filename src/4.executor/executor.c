/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:44:27 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/20 14:13:18 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file executor.c
 * @brief This file contains the executor functions
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/05/06
*/

#include "minishell.h"

char	**separate_args(t_token *token)
{
	t_token	*tmp;
	char	**cmd;
	int		i;
	int		size_token;

	tmp = token;
	i = 0;
	size_token = 0;
	while (tmp)
	{
		tmp = tmp->next;
		size_token++;
	}
	cmd = (char **)allocate(sizeof(char *) * (size_token + 1));
	if (!cmd)
		return (NULL);
	tmp = token;
	while (tmp)
	{
		cmd[i] = ft_strdup(tmp->lexeme);
		typetree_insert(cmd[i]);
		tmp = tmp->next;
		i++;
	}
	cmd[i] = NULL;
	return (cmd);
}

void	exec_init(char ***cmd, int *exit_status, t_bin *bin, t_data **data)
{
	t_token	*token;

	token = lexer(bin->cmd);
	*cmd = separate_args(token);
	if (bin->type == CMD)
		expander_validation(data, *cmd);
	typetree_insert(*cmd);
	*exit_status = check_exec_builtin(*cmd, &(*data)->my_envp, *data);
}

int	verify_cmd(char **cmd)
{
	int	idx;

	if (cmd == NULL)
		return (0);
	idx = 0;
	while (cmd[idx])
	{
		if (verify_line(&cmd[idx]) == 0 && cmd[idx + 1] != NULL)
		{
			while (cmd[idx + 1])
			{
				cmd[idx] = cmd[idx + 1];
				idx++;
			}
			cmd[idx] = NULL;
			idx = 0;
			continue ;
		}
		else if (verify_line(&cmd[idx]) == 0)
			return (0);
		idx++;
	}
	return (1);
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
	else if (!verify_cmd(cmd))
		return (0);
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
	else if (is_redirect(bin->type))
		return (exec_redirect(bin, data));
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
