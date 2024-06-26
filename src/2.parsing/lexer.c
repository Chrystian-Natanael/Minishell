/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 09:30:45 by krocha-h          #+#    #+#             */
/*   Updated: 2024/06/20 16:06:41 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file lexer.c
 * @brief This file contains the lexer functions
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/05/01
*/

#include "minishell.h"

char	*get_word(char *line, int *i, int *state)
{
	int		tmp;
	int		idx;
	char	*word;

	tmp = *i;
	idx = 0;
	while (line[*i] && !is_metacharacter(line[*i], line[(*i) + 1])
		&& !ft_isspace(line[*i]))
	{
		if (line[*i] == '\'' || line[*i] == '"')
			idx += close_quote(line, &i);
		idx++;
		(*i)++;
	}
	if (is_metacharacter(line[*i], 0))
		(*state)++;
	if (quote_is_closed(line, i) == 0)
		return (NULL);
	word = allocate(sizeof(char) * (idx + 1));
	idx = 0;
	while (tmp < *i && line[tmp])
		word[idx++] = line[tmp++];
	word[idx] = '\0';
	return (word);
}

char	*quote_word(char *line, int *i)
{
	char	*word;
	char	type_quote;
	int		quote;
	int		size;
	int		tmp;

	size = 0;
	tmp = *i;
	type_quote = line[(*i)];
	quote = 0;
	while (line[*i] && !(!(quote % 2 != 0)
			&& ft_isspace(line[(*i)])))
	{
		if (line[*i] == type_quote)
			quote++;
		size++;
		(*i)++;
	}
	if (!line[tmp] || size == 0 || (quote % 2 != 0))
		return (NULL);
	word = allocate(sizeof(char) * (size + 1));
	size = 0;
	while (tmp < *i)
		word[size++] = line[tmp++];
	return (word);
}

char	*get_token_word(char *line, int *i, int *type, int *state)
{
	char	*word;

	if (line[*i] == '\0')
		return (NULL);
	word = NULL;
	if (line[*i] == '"' || line[*i] == '\'')
		word = quote_word(line, i);
	else
		word = get_word(line, i, state);
	if (word)
		*type = WORD;
	return (word);
}

void	meta_double(int token_type, char c, int *i, int *state)
{
	if (token_type >= OR || c == ')')
	{
		if (token_type >= OR)
			(*i)++;
		(*i)++;
		*state = 1;
	}
}

t_token	*lexer(char *line)
{
	int		i;
	int		state;
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
		state = 0;
		meta_double(token_type, line[i], &i, &state);
		if (token_type < 0)
			word = get_token_word(line, &i, &token_type, &state);
		if (token_type >= 0)
			lst_addnew(&list, token_type, word);
		word = NULL;
		if (line[i] != '\0' && line[i] != ')' && state == 0)
			i++;
	}
	return (list);
}
