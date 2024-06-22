/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:18:57 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/21 22:04:06 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file cmd.c
 * @brief This file contains the cmd functions
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/05/01
*/

#include "minishell.h"

void	pop_redirects(t_organize *organize, int *odx, t_token **token)
{
	organize->count_redir = count_redirects(organize->tmp);
	organize->redir = allocate(sizeof(t_token *) * (organize->count_redir + 1));
	while (organize->count_redir--)
	{
		organize->redir[*odx] = allocate(sizeof(t_aux_redirect));
		organize->redir[*odx]->redir = lstpop(token, organize->idx);
		organize->redir[*odx]->file_name = lstpop(token, organize->idx);
		organize->tmp = *token;
		organize->idx = 0;
		while ((organize->tmp && !is_redirect(organize->tmp->type)
				&& organize->count_redir)
			|| organize->idx < organize->point)
		{
			organize->tmp = organize->tmp->next;
			organize->idx++;
		}
		(*odx)++;
	}
}

void	push_redirects(t_organize *organize, int *odx)
{
	*odx = 0;
	while (organize->redir[*odx])
	{
		organize->redir[*odx]->redir->next = organize->redir[*odx]->file_name;
		if (organize->redir[*odx + 1])
			organize->redir[*odx]->file_name->next = \
			organize->redir[*odx + 1]->redir;
		(*odx)++;
	}
	organize->idx += (2 * (*odx)) + 1;
	organize->redir[*odx - 1]->file_name->next = organize->tmp->next;
	organize->tmp->next = organize->redir[0]->redir;
	organize->tmp = organize->redir[*odx - 1]->file_name->next;
	organize->redir = NULL;
}

void	organize_redirects(t_token **token)
{
	int				odx;
	t_organize		organize;

	init_organize(&organize, token);
	while (organize.tmp)
	{
		odx = 0;
		organize.count_redir = 1;
		if (is_redirect(organize.tmp->type) && organize.tmp->next
			&& organize.tmp->next->next
			&& organize.tmp->next->next->type == WORD)
			pop_redirects(&organize, &odx, token);
		organize.point = organize.idx;
		if ((organize.tmp && organize.tmp->next
				&& organize.tmp->next->type != WORD && organize.redir)
			|| (organize.tmp && !organize.tmp->next && organize.redir))
			push_redirects(&organize, &odx);
		if (organize.tmp)
			organize.tmp = organize.tmp->next;
		organize.idx++;
	}
}

t_token	*cmd_parsing(t_token *token)
{
	t_parsing	parsing;

	init_parsing(&parsing, &token);
	organize_redirects(&parsing.tmp);
	while (parsing.tmp)
	{
		if (parsing.tmp && parsing.tmp->type == L_PAREN)
			if (!is_sub_shell(&parsing))
				return (NULL);
		if (parsing.tmp && (is_redirect(parsing.tmp->type)
				|| parsing.tmp->type == FILE_NAME))
		{
			cmd_parsing_aux(&parsing.head, &parsing.cmds, &parsing.tmp);
			lst_contatenate_redir(&parsing.cmds, parsing.tmp->lexeme);
			parsing.tmp = parsing.tmp->next;
		}
		else
			is_cmd(&parsing);
		cmd_parsing_aux(&parsing.head, &parsing.cmds, &parsing.tmp);
	}
	return (parsing.head);
}

void	cmd_parsing_aux(t_token **head, t_token **cmds, t_token **tmp)
{
	t_token	*aux;

	lstadd_back(head, *cmds);
	if (*cmds != NULL)
		*cmds = (*cmds)->next;
	if (*tmp && (((*tmp)->type == PIPE || (*tmp)->type == OR
				|| (*tmp)->type == AND) || (*tmp)->type == L_PAREN
			|| (*tmp)->type == R_PAREN || is_redirect((*tmp)->type)))
	{
		aux = (*tmp)->next;
		(*tmp)->next = NULL;
		(*tmp)->lexeme = return_lexeme(*tmp);
		lstadd_back(head, *tmp);
		*tmp = aux;
	}
}
