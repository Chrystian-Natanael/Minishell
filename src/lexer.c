/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 09:30:45 by cnatanae          #+#    #+#             */
/*   Updated: 2024/05/11 16:31:58 by krocha-h         ###   ########.fr       */
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
	int	s_quote;
	int	d_quote;
	int	tmp;

	tmp = *i;
	s_quote = 0;
	d_quote = 0;
	while (line[tmp] && !is_metacharacter(line[tmp], line[(tmp) + 1])
		&& !ft_isspace(line[tmp]))
	{
		if (line[tmp] == '"')
			d_quote++;
		else if (line[tmp] == '\'')
			s_quote++;
		tmp++;
	}
	if (s_quote % 2 == 0 || d_quote % 2 == 0)
		return (1);
	return (0);
}

char	*get_word(char *line, int *i)
{
	int		tmp;
	int		idx;
	int		quote;
	char	*word;

	printf("entrando em get_word\n");
	tmp = *i;
	idx = 0;
	while (line[*i] && !is_metacharacter(line[*i], line[(*i) + 1])
		&& !ft_isspace(line[*i]))
	{
		idx++;
		(*i)++;
	}
	word = allocate(sizeof(char) * (idx + 1));
	quote = quote_is_closed(line, i);
	idx = 0;
	while (tmp < *i)
	{
		if (quote)
		{
			if (line[(tmp)] == '"' || line[(tmp)] == '\'')
				tmp++;
		}
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

	printf("entrando em get_token_word\n");
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
	int		token_type;
	char	*word;
	t_token	*list;

	printf("line = %s\n", line);
	printf("entrando no lexer\n");
	i = 0;
	list = NULL;
	word = NULL;
	while (line && line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		token_type = get_token_type(line, i);
		if (token_type >= OR)
			i++;
		if (token_type < 0)
		{
			word = get_token_word(line, &i, &token_type);
			printf("word = %s\n", word);
		}
		lst_addnew(&list, token_type, word);
		word = NULL;
		if (line[i] != '\0')
			i++;
		printf("i = %d\n", i);
		printf("line[i] = %c\n", line[i]);
	}
	return (list);
}
