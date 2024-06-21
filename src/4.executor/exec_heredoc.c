/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:55:41 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/21 16:03:46 by cnatanae         ###   ########.fr       */
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
static int	heredoc_loop(t_heredoc *heredoc, const int std_in, t_data **data, int expansible);

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

void	expander_var(int *i, char **buff, t_envp **envp, char **dst)
{
	char	*line;
	char	*key;
	int		size;

	line = NULL;
	key = NULL;
	if (!buff || !*buff || ft_isdigit((*buff)[*i + 1]))
		return ;
	if (*dst)
	{
		line = ft_strdup(*dst);
		typetree_insert(line);
	}
	size = ++(*i);
	while ((*buff) && (*buff)[size] && is_valid_var((*buff)[size]))
	{
		if ((*buff)[size - 1] == '$' && (*buff)[size] == '?' && size == (*i))
		{
			size++;
			break ;
		}
		size++;
	}
	key = ft_substr(*buff, (*i), size - (*i));
	typetree_insert(key);
	if (!line)
		line = ft_strdup("");
	line = ft_strjoin(line, envp_get(key, *envp));
	typetree_insert(line);
	if ((*buff)[size] == '?')
		size++;
	*i = size - 1;
	(*dst) = line;
}

static void	expander_heredoc(t_data **data, char **buff)
{
	int		i;
	char	*line;

	i = -1;
	line = NULL;
	while ((*buff)[++i])
	{
		if ((*buff)[i] == '$' && (*buff)[i + 1] && is_valid_var((*buff)[i + 1]))
			expander_var(&i, buff, &(*data)->my_envp, &line);
		else
			add_char(&line, (*buff)[i]);
	}
	*buff = line;
}

static int	remove_quote_eof(char **eof)
{
	int		i;
	int		expansible;
	int		size;
	char	*line;

	i = -1;
	size = ft_strlen(*eof);
	expansible = 0;
	line = allocate(size - 1);
	while ((*eof)[++i])
	{
		if ((*eof)[i] == '\'' || (*eof)[i] == '\"')
			expansible = 1;
		else
			add_char(&line, (*eof)[i]);
	}
	if ((*eof)[0] == '$')
		expansible = 1;
	*eof = line;
	return (expansible);
}

static int	heredoc_loop(t_heredoc *heredoc, const int std_in, t_data **data, int expansible)
{

	heredoc->buff = readline("> ");
	typetree_insert(heredoc->buff);
	if (g_sign == SIGINT)
	{
		dup2(std_in, STDIN_FILENO);
		return (0);
	}
	if (!heredoc->buff || !ft_strncmp(heredoc->buff, heredoc->eof, ft_strlen(heredoc->eof) + 1))
		return (0);
	if (!expansible)
		expander_heredoc(data, &heredoc->buff);
	ft_putstr_fd(heredoc->buff, heredoc->fd);
	write(heredoc->fd, "\n", 1);
	heredoc->buff = NULL;
	return (1);
}

int	exec_heredoc(t_token **token, int *count_files, t_data **data)
{
	t_heredoc	heredoc;
	int			expansible;
	const int	std_in = dup(STDIN_FILENO);

	heredoc.eof = (*token)->next->lexeme;
	if (!heredoc_file_creation(1, &(heredoc.fd), &(heredoc.fl_name)))
		return (0);
	expansible = remove_quote_eof(&(heredoc.eof));
	while (heredoc_loop(&heredoc, std_in, data, expansible))
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
			if (exec_heredoc(&tmp, &(*data)->count_files, data) == -1)
				break ;
		}
		tmp = tmp->next;
	}
}
