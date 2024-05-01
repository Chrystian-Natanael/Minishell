/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 09:30:45 by cnatanae          #+#    #+#             */
/*   Updated: 2024/05/01 18:52:44 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file lexer.c
 * @brief This file contains the lexer functions
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/05/01
*/

#include "minishell.h"

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

char	*quote_word(char *line, int *i)
{
	char	*word;
	int		size;
	int		idx;
	int		teste;

	idx = 0;
	size = 0;
	teste = *i;
	if (line[*i] == '"')
	{
		while (line && line[++(*i)] != '"')
			size++;
	}
	else if (line[*i] == '\'')
	{
		while (line && line[++(*i)] != '\'')
			size++;
	}
	word = allocate(sizeof(char) * (size + 1));
	if (line[teste] == '"')
	{
		while (line && line[++teste] != '"')
			word[idx++] = line[teste];
	}
	else if (line[teste] == '\'')
	{
		while (line && line[++teste] != '\'')
			word[idx++] = line[teste];
	}
	if (line[teste] == '\'' || line[teste] == '\'')
	{
		word[size] = '\0';
		return (word);
	}
	return (NULL);
}

char	*get_token_word(char *line, int *i, int *type)
{
	char	*word;

	word = NULL;
	if (line[*i] == '"' || line[*i] == '\'')
		word = quote_word(line, i);
	if (word)
		*type = WORD;
	return (word);
}

t_token	*lexer(char *line)
{
	int		i;
	int		token_type;
	t_token	*list;
	char	*word;

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
		if (token_type < WORD)
			word = get_token_word(line, &i, &token_type);
		lst_addnew(&list, token_type, word);
		if (line[i] != '\0')
			i++;
	}
	return (list);
}
