/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 10:58:04 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/21 17:59:09 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief This function executes the redirection input command
 * @param bin the command to be executed
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/06/07
*/

#include "minishell.h"

void	remove_quotes(char **cmd)
{
	int		idx;
	char	*line;

	idx = 0;
	line = NULL;
	while ((*cmd) && (*cmd)[idx])
	{
		if ((*cmd)[idx] != '\'' && (*cmd)[idx] != '\"')
			add_char(&line, (*cmd)[idx]);
		idx++;
	}
	*cmd = line;
}

void	open_redirect(t_bin *bin)
{
	remove_quotes(&bin->right->cmd);
	if (bin->type == REDIR_INPUT && bin->right->cmd)
		bin->fd = open(bin->right->cmd, O_RDONLY);
	else if (bin->type == REDIR_OUTPUT && bin->right->cmd)
		bin->fd = open(bin->right->cmd, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (bin->type == OUTPUT_APPEND && bin->right->cmd)
		bin->fd = open(bin->right->cmd, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		bin->fd = -1;
}

int	open_files(t_bin *bin)
{
	int	status;

	status = 0;
	if ((bin->left && is_redirect(bin->left->type)) && bin->left->fd != -1)
		status = open_files(bin->left);
	if ((bin->left && bin->left->fd != -1) || !bin->left)
		open_redirect(bin);
	if ((bin->left && bin->left->fd != -1 && bin->fd == -1)
		|| (bin->fd == -1 && !bin->left))
		return (ft_error("minishell: ", bin->right->cmd, \
		": No such file or directory", 1));
	else if (bin->left && bin->left->fd == -1)
	{
		bin->fd = -1;
		return (status);
	}
	if (is_redirect_input(bin->type))
		dup2(bin->fd, STDIN_FILENO);
	else
		dup2(bin->fd, STDOUT_FILENO);
	close(bin->fd);
	return (status);
}

void	close_dup_fd(const int *fd)
{
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
}

int	exec_redirect(t_bin *bin, t_data **data)
{
	int			status;
	const int	keep_fd[2] = {dup(STDIN_FILENO), dup(STDOUT_FILENO)};

	status = 0;
	if (!bin->fd)
		status = open_files(bin);
	if (status == 1 || (bin && bin->fd == -1))
	{
		close_dup_fd(keep_fd);
		return (status);
	}
	if (bin->left)
		status = exec_tree(bin->left, data);
	else if (!bin->left && bin->fd == -1)
		status = -1;
	else
		status = 0;
	close_dup_fd(keep_fd);
	return (status);
}
