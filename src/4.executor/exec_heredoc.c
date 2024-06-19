/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:55:41 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/18 21:45:54 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function executes the heredoc command
 * @param bin the command to be executed
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/06/07
*/

static int	heredoc_file_creation(int count, int *fd, char **fl_name);
static int	heredoc_loop(char **buff, char *eof, const int std_in, int fd);

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

static int	heredoc_loop(char **buff, char *eof, const int std_in, int fd)
{
	*buff = readline("> ");
	if (g_sign == SIGINT)
	{
		dup2(std_in, STDIN_FILENO);
		return (0);
	}
	(void)std_in;
	if (!*buff || !ft_strncmp(*buff, eof, ft_strlen(eof) + 1))
		return (0);
	ft_putstr_fd(*buff, fd);
	write(fd, "\n", 1);
	free(*buff);
	*buff = NULL;
	return (1);
}

int	exec_heredoc(t_token **token, int *count_files)
{
	int			fd;
	char		*buff;
	char		*fl_name;
	char		*eof;
	const int	std_in = dup(STDIN_FILENO);

	eof = (*token)->next->lexeme;
	if (!heredoc_file_creation(1, &fd, &fl_name))
		return (0);
	while (heredoc_loop(&buff, eof, std_in, fd))
		;
	close(fd);
	close (std_in);
	if (g_sign == SIGINT)
		return (-1);
	if (*token && (*token)->type == HEREDOC)
		(*token)->type = REDIR_INPUT;
	if (token && (*token)->next->type == WORD)
	{
		(*token)->next->lexeme = fl_name;
		(*token)->next->type = FILE_NAME;
	}
	*count_files += 1;
	return (0);
}

void	heredoc_validation(t_token **tokens, int *count_files)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
		{
			heredoc_signals();
			if (exec_heredoc(&tmp, count_files) == -1)
				break ;
		}
		tmp = tmp->next;
	}
}
