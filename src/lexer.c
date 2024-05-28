/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 09:30:45 by cnatanae          #+#    #+#             */
/*   Updated: 2024/05/28 10:11:29 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file lexer.c
 * @brief This file contains the lexer functions
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/05/01
*/

#include "minishell.h"

int	quote_is_closed(char *line, int *i)
{
	int	tmp;

	tmp = *i;
	while (line[tmp] && !is_metacharacter(line[tmp], line[(tmp) + 1])
		&& !ft_isspace(line[tmp]))
	{
		if (line[tmp] == '"')
		{
			while (line[tmp] != '\0' && line[tmp] != '"')
				tmp++;
			if (line[tmp] == '\0')
				return (0);
		}
		else if (line[tmp] == '\'')
		{
			while (line[tmp] != '\0' && line[tmp] != '\'')
				tmp++;
			if (line[tmp] == '\0')
				return (0);
		}
		tmp++;
	}
	return (1);
}

char	*get_word(char *line, int *i)
{
	int		tmp;
	int		idx;
	int		quote;
	char	*word;

	tmp = *i;
	idx = 0;
	while (line[*i] && !is_metacharacter(line[*i], line[(*i) + 1])
		&& !ft_isspace(line[*i]))
	{
		idx++;
		(*i)++;
	}
	quote = quote_is_closed(line, i);
	if (quote == 0)
		return (NULL);
	word = allocate(sizeof(char) * (idx + 1));
	idx = 0;
	while (tmp < *i)
	{
		if (quote)
			if (line[(tmp)] == '"') // || line[(tmp)] == '\'') aspas simples não expande var
				tmp++;
		word[idx++] = line[tmp++];
	}
	word[idx] = '\0';
	return (word);
}

char	*quote_word(char *line, int *i)
{
	char	*word;
	char	quote;
	int		size;
	int		idx;
	int		tmp;

	size = 0;
	tmp = *i + 1;
	quote = line[(*i)++];
	while (line[*i] && line[(*i)] != quote)
	{
		size++;
		(*i)++;
	}
	if (!line[*i])
		return (NULL);
	word = allocate(sizeof(char) * (size + 1));
	idx = 0;
	while (tmp < *i)
		word[idx++] = line[tmp++];
	word[size] = '\0';
	return (word);
}

char	*get_token_word(char *line, int *i, int *type)
{
	char	*word;

	word = NULL;
	if (line[*i] == '"' || line[*i] == '\'')
		word = quote_word(line, i);
	else
		word = get_word(line, i);
	if (word)
		*type = WORD;
	return (word);
}

int	get_token_type(char *line, int i)
{
	if (line[i] == '(')
		return (L_PAREN);
	else if (line[i] == ')')
		return (R_PAREN);
	else if (line[i] == '$')
		return (DOLLAR);
	else if (line[i] == '<' && line[i + 1] == '<')
		return (HEREDOC);
	else if (line[i] == '<')
		return (REDIR_INPUT);
	else if (line[i] == '>' && line[i + 1] == '>')
		return (OUTPUT_APPEND);
	else if (line[i] == '>')
		return (REDIR_OUTPUT);
	else if (line[i] == '|' && line[i + 1] == '|')
		return (OR);
	else if (line[i] == '|')
		return (PIPE);
	else if (line[i] == '&' && line[i + 1] == '&')
		return (AND);
	else
		return (-1);
}

t_token	*lexer(char *line)
{
	int		i;
	int		boolean;
	int		token_type;
	char	*word;
	t_token	*list;

	i = 0;
	list = NULL;
	word = NULL;
	while (line && line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		token_type = get_token_type(line, i);
		boolean = 0;
		if (token_type >= OR || line[i] == ')')
		{
			if (token_type >= OR)
				i++;
			i++;
			boolean = 1;
		}
		if (token_type < 0)
			word = get_token_word(line, &i, &token_type);
		if (token_type >= 0)
			lst_addnew(&list, token_type, word);
		else
			return (NULL);
		word = NULL;
		if (line[i] != '\0' && line[i] != ')' && boolean == 0)
			i++;
	}
	return (list);
}
