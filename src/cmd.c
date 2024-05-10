/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:18:57 by cnatanae          #+#    #+#             */
/*   Updated: 2024/05/10 12:59:52 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file cmd.c
 * @brief This file contains the cmd functions
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/05/01
*/

#include "minishell.h"

t_token	*cmd_parsing(t_token *token)
{
	t_token	*tmp;
	t_token	*cmds;
	t_token	*head;

	cmds = NULL;
	tmp = token;
	head = NULL;
	while (tmp)
	{
		while (tmp->type != PIPE && tmp->type != OR
			&& tmp->type != AND && tmp->type != L_PAREN && tmp->type != R_PAREN)
		{
			if ((tmp->lexema && *tmp->lexema != '\0') || tmp->type != WORD)
				lst_contatenate(&cmds, return_lexema(tmp));
			tmp = tmp->next;
			if (!tmp)
				break ;
		}
		cmd_parsing_aux(&head, &cmds, &tmp);
	}
	return (head);
}

char	*return_lexema(t_token *token)
{
	if (token->type == WORD || token->type == EXPRESSION)
		return (token->lexema);
	else if (token->type == REDIR_INPUT)
		return ("<<");
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
	else if (token->type == DOLLAR)
		return ("$");
	else if (token->type == PIPE)
		return ("|");
	else if (token->type == OR)
		return ("||");
	else if (token->type == AND)
		return ("&&");
	else
		return ("");
}

void	cmd_parsing_aux(t_token **head, t_token **cmds, t_token **tmp)
{
	t_token	*aux;

	lstadd_back(head, *cmds);
	if (*cmds != NULL)
		*cmds = (*cmds)->next;
	if (*tmp && (((*tmp)->type == PIPE || (*tmp)->type == OR
			|| (*tmp)->type == AND) || (*tmp)->type == L_PAREN || (*tmp)->type == R_PAREN))
	{
		aux = (*tmp)->next;
		(*tmp)->next = NULL;
		(*tmp)->lexema = return_lexema(*tmp);
		lstadd_back(head, *tmp);
		*tmp = aux;
	}
	else if (*tmp)
			*tmp = (*tmp)->next;
}

void	lst_contatenate(t_token **list, char *lexema)
{
	t_token	*new;
	t_token	*tmp;

	tmp = *list;
	new = (t_token *)allocate(sizeof(t_token));
	new->type = EXPRESSION;
	new->lexema = lexema;
	new->next = NULL;
	if (*list == NULL)
		*list = new;
	else
	{
		(*list)->lexema = ft_strjoin((*list)->lexema, " ");
		typetree_insert((*list)->lexema);
		(*list)->lexema = ft_strjoin((*list)->lexema, lexema);
		typetree_insert((*list)->lexema);
	}
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
