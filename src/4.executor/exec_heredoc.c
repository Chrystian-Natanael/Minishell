/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:55:41 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/21 15:14:13 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief This function executes the heredoc command
 * @param bin the command to be executed
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/06/07
*/

#include "minishell.h"

static int	heredoc_file_creation(int count, int *fd, char **fl_name);
static int	heredoc_loop(t_heredoc *heredoc, const int std_in);

static int	heredoc_file_creation(int count, int *fd, char **fl_name)
{
	static long int	result;

	result += count;
	*fl_name = ft_strmerge(ft_strdup("/tmp/heredoc-0x"), ft_itoa(result));
	typetree_insert(*fl_name);
	if (!*fl_name)
		return (0);
	*fd = open(*fl_name, TRUN, 0666);
	if (*fd >= 0)
		return (1);
	return (0);
}

static int	heredoc_loop(t_heredoc *heredoc, const int std_in)
{
	heredoc->buff = readline("> ");
	if (g_sign == SIGINT)
	{
		dup2(std_in, STDIN_FILENO);
		return (0);
	}
	(void)std_in;
	if (!heredoc->buff || !ft_strncmp(heredoc->buff, heredoc->eof, ft_strlen(heredoc->eof) + 1))
		return (0);
	ft_putstr_fd(heredoc->buff, heredoc->fd);
	write(heredoc->fd, "\n", 1);
	free(heredoc->buff);
	heredoc->buff = NULL;
	return (1);
}

int	exec_heredoc(t_token **token, int *count_files)
{
	t_heredoc	heredoc;
	const int	std_in = dup(STDIN_FILENO);

	heredoc.eof = (*token)->next->lexeme;
	if (!heredoc_file_creation(1, &(heredoc.fd), &(heredoc.fl_name)))
		return (0);
	while (heredoc_loop(&heredoc, std_in))
		;
	close(heredoc.fd);
	close (std_in);
	if (g_sign == SIGINT)
		return (-1);
	if (*token && (*token)->type == HEREDOC)
		(*token)->type = REDIR_INPUT;
	if (token && (*token)->next->type == WORD)
	{
		(*token)->next->lexeme = heredoc.fl_name;
		(*token)->next->type = FILE_NAME;
	}
	*count_files += 1;
	return (0);
}

void	heredoc_validation(t_data **data)
{
	t_token	*tmp;

	tmp = (*data)->token;
	while (tmp)
	{
		if (tmp->type == HEREDOC && tmp->next && tmp->next->type == WORD)
		{
			heredoc_signals();
			if (exec_heredoc(&tmp, &(*data)->count_files) == -1)
				break ;
		}
		tmp = tmp->next;
	}
}
