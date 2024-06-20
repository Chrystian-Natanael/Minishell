/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 17:06:11 by krocha-h          #+#    #+#             */
/*   Updated: 2024/06/20 16:25:26 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file utils_3.c
 * @brief This file contains the pwd function
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/06/01
*/

#include "minishell.h"

int	get_token_type(char *line, int i)
{
	if (line[i] == '(')
		return (L_PAREN);
	else if (line[i] == ')')
		return (R_PAREN);
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

char	*return_lexeme(t_token *token)
{
	if (!token)
		return ("");
	if (token->type == WORD || token->type == CMD)
		return (token->lexeme);
	else if (token->type == REDIR_INPUT)
		return ("<");
	else if (token->type == REDIR_OUTPUT)
		return (">");
	else if (token->type == OUTPUT_APPEND)
		return (">>");
	else if (token->type == HEREDOC)
		return ("<<");
	else if (token->type == L_PAREN)
		return ("(");
	else if (token->type == R_PAREN)
		return (")");
	else if (token->type == PIPE)
		return ("|");
	else if (token->type == OR)
		return ("||");
	else if (token->type == AND)
		return ("&&");
	else
		return ("");
}

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

int	close_quote(char *line, int **i)
{
	int		size;
	char	type_quote;

	type_quote = line[(**i)++];
	size = 1;
	while (line[**i] && line[**i] != type_quote)
	{
		(**i)++;
		size++;
	}
	if (!line[**i] || line[**i] != type_quote)
		return (0);
	return (size);
}

int	is_metacharacter(char a, char b)
{
	if (a == '|' || a == '(' || a == ')' || a == '<' || a == '>')
		return (1);
	else if (a == '&' && b == '&')
		return (1);
	return (0);
}
