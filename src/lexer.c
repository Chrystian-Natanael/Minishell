/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 09:30:45 by cnatanae          #+#    #+#             */
/*   Updated: 2024/05/01 09:32:03 by cnatanae         ###   ########.fr       */
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

void	lst_addnew(t_token **list, enum e_token type, char *lexema)
{
	t_token	*new;
	t_token	*tmp;

	tmp = *list;
	new = (t_token *)allocate(sizeof(t_token));
	new->type = type;
	new->lexema = lexema;
	new->next = NULL;
	if (*list == NULL)
		*list = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_token	*lexer(char *line)
{
	int		i;
	int		token_type;
	t_token	*list;

	i = 0;
	list = NULL;
	while (line && line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		token_type = get_token_type(line, i);
		if (token_type >= OR)
			i++;
		if (token_type != -1)
			lst_addnew(&list, token_type, NULL);
		if (line[i] != '\0')
			i++;
	}
	return (list);
}
