/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 17:06:11 by krocha-h          #+#    #+#             */
/*   Updated: 2024/06/18 21:46:14 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file utils_3.c
 * @brief This file contains the pwd function
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/06/01
*/

#include "minishell.h"

char	*ft_strndup(const char *s, int n)
{
	char	*dup;
	int		idx;

	dup = ft_calloc(n + 1, sizeof(char));
	if (!dup)
		return (NULL);
	idx = 0;
	while (*s && idx < n)
		dup[idx++] = *(s++);
	return (dup);
}

int	ternary(int condition, int if_true, int if_false)
{
	if (condition)
		return (if_true);
	return (if_false);
}

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

void	lstadd_back(t_token **lst, t_token *new)
{
	t_token	*aux;

	aux = *lst;
	if (aux == NULL)
	{
		*lst = new;
		return ;
	}
	while (aux->next)
		aux = aux->next;
	aux->next = new;
}
