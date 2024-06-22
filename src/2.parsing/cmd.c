/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:18:57 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/21 21:20:56 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file cmd.c
 * @brief This file contains the cmd functions
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/05/01
*/

#include "minishell.h"

void	organize_redirects(t_token **token)
{
	int				idx;
	int				odx;
	int				point;
	int				count_redir;
	t_token			*tmp;
	t_aux_redirect	**redir;

	tmp = *token;
	idx = 0;
	redir = NULL;
	point = 0;
	while (tmp)
	{
		odx = 0;
		count_redir = 1;
		if (is_redirect(tmp->type) && tmp->next && tmp->next->next && tmp->next->next->type == WORD)
		{
			count_redir = count_redirects(tmp);
			redir = allocate(sizeof(t_token *) * (count_redir + 1));
			while (count_redir--)
			{
				redir[odx] = allocate(sizeof(t_aux_redirect));
				redir[odx]->redir = lstpop(token, idx);
				redir[odx]->file_name = lstpop(token, idx);
				tmp = *token;
				idx = 0;
				while ((tmp && !is_redirect(tmp->type) && count_redir)
					|| idx < point)
				{
					tmp = tmp->next;
					idx++;
				}
				odx++;
			}
		}
		point = idx;
		if ((tmp && tmp->next && tmp->next->type != WORD && redir)
			|| (tmp && !tmp->next && redir))
		{
			odx = 0;
			while (redir[odx])
			{
				redir[odx]->redir->next = redir[odx]->file_name;
				if (redir[odx + 1])
					redir[odx]->file_name->next = redir[odx + 1]->redir;
				odx++;
			}
			idx += (2 * odx) + 1;
			redir[odx - 1]->file_name->next = tmp->next;
			tmp->next = redir[0]->redir;
			tmp = redir[odx - 1]->file_name->next;
			redir = NULL;
		}
		if (tmp)
			tmp = tmp->next;
		idx++;
	}
}

void	init_parsing(t_parsing *parsing, t_token **token)
{
	parsing->i = 0;
	parsing->tmp = *token;
	parsing->cmds = NULL;
	parsing->head = NULL;
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
		if (parsing.tmp && (is_redirect(parsing.tmp->type) || parsing.tmp->type == FILE_NAME))
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
