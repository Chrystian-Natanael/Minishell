/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:18:57 by cnatanae          #+#    #+#             */
/*   Updated: 2024/05/03 17:43:20 by cnatanae         ###   ########.fr       */
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
		while (tmp->type != PIPE && tmp->type != OR && tmp->type != AND)
		{
			lst_contatenate(&cmds, tmp->lexema);
			tmp = tmp->next;
			if (!tmp)
				break ;
		}
		cmd_parsing_aux(&head, &cmds, &tmp);
	}
	return (head);
}

void	cmd_parsing_aux(t_token **head, t_token **cmds, t_token **tmp)
{
	t_token	*aux;

	lstadd_back(head, *cmds);
	if (*cmds != NULL)
		*cmds = (*cmds)->next;
	if (*tmp && ((*tmp)->type == PIPE || (*tmp)->type == OR
			|| (*tmp)->type == AND))
	{
		aux = (*tmp)->next;
		(*tmp)->next = NULL;
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
