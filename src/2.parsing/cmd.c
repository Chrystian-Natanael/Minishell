/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:18:57 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/21 19:39:14 by cnatanae         ###   ########.fr       */
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
	int				idx[2];
	int				point;
	int				count_redir;
	t_token			*tmp;
	t_aux_redirect	**redir;

	tmp = *token;
	idx[0] = 0;
	redir = NULL;
	point = 0;
	while (tmp)
	{
		idx[1] = 0;
		count_redir = 1;
		if (is_redirect(tmp->type) && tmp->next && tmp->next->next
			&& tmp->next->next->type == WORD)
		{
			count_redir = count_redirects(tmp);
			redir = allocate(sizeof(t_token *) * (count_redir + 1));
			while (count_redir--)
			{
				redir[idx[1]] = allocate(sizeof(t_aux_redirect));
				redir[idx[1]]->redir = lstpop(token, idx);
				redir[idx[1]]->file_name = lstpop(token, idx);
				tmp = *token;
				idx[0] = 0;
				while ((tmp && !is_redirect(tmp->type) && count_redir)
					|| idx < point)
				{
					tmp = tmp->next;
					idx[0]++;
				}
				idx[1]++;
			}
		}
		point = idx[0];
		if ((tmp && tmp->next && tmp->next->type != WORD && redir)
			|| (tmp && !tmp->next && redir))
		{
			idx[1] = 0;
			while (redir[idx[1]])
			{
				redir[idx[1]]->redir->next = redir[idx[1]]->file_name;
				if (redir[idx[1] + 1])
					redir[idx[1]]->file_name->next = redir[idx[1] + 1]->redir;
				idx[1]++;
			}
			idx[0] += (2 * idx[1]) + 1;
			redir[idx[1] - 1]->file_name->next = tmp->next;
			tmp->next = redir[0]->redir;
			tmp = redir[idx[1] - 1]->file_name->next;
			redir = NULL;
		}
		if (tmp)
			tmp = tmp->next;
		idx[0]++;
	}
}

t_token	*cmd_parsing(t_token *token, t_envp **envp)
{
	int		i;
	t_token	*tmp;
	t_token	*cmds;
	t_token	*head;

	cmds = NULL;
	head = NULL;
	tmp = token;
	(void)envp;
	i = 0;
	organize_redirects(&tmp);
	while (tmp)
	{
		if (tmp && tmp->type == L_PAREN)
		{
			i++;
			while (tmp && (tmp->type != R_PAREN || i != 0))
			{
				lst_contatenate(&cmds, return_lexeme(tmp));
				tmp = tmp->next;
				if (tmp && tmp->type == R_PAREN)
					i--;
				else if (tmp && tmp->type == L_PAREN)
					i++;
			}
			if (tmp && tmp->type == R_PAREN)
				lst_contatenate(&cmds, return_lexeme(tmp));
			if (!tmp && i != 0)
				return (NULL);
			tmp = tmp->next;
			cmds->type = SUB_SHELL;
		}
		if (tmp && (is_redirect(tmp->type || tmp->type == FILE_NAME)))
		{
			cmd_parsing_aux(&head, &cmds, &tmp);
			lst_contatenate_redir(&cmds, tmp->lexeme);
			tmp = tmp->next;
		}
		else
		{
			while (tmp && tmp->type != PIPE && tmp->type != OR
				&& tmp->type != AND && tmp->type != L_PAREN
				&& tmp->type != R_PAREN && !is_redirect(tmp->type))
			{
				if ((tmp->lexeme && *tmp->lexeme != '\0') || tmp->type != WORD)
					lst_contatenate(&cmds, return_lexeme(tmp));
				tmp = tmp->next;
			}
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

void	lst_contatenate(t_token **list, char *lexeme)
{
	t_token	*new;

	new = (t_token *)allocate(sizeof(t_token));
	new->type = CMD;
	new->lexeme = lexeme;
	new->next = NULL;
	if (*list == NULL)
		*list = new;
	else
	{
		(*list)->lexeme = ft_strjoin((*list)->lexeme, " ");
		typetree_insert((*list)->lexeme);
		(*list)->lexeme = ft_strjoin((*list)->lexeme, lexeme);
		typetree_insert((*list)->lexeme);
	}
}

void	lst_contatenate_redir(t_token **list, char *lexeme)
{
	t_token	*new;

	new = (t_token *)allocate(sizeof(t_token));
	new->type = FILE_NAME;
	new->lexeme = lexeme;
	new->next = NULL;
	if (*list == NULL)
		*list = new;
	else
	{
		(*list)->lexeme = ft_strjoin((*list)->lexeme, lexeme);
		typetree_insert((*list)->lexeme);
	}
}
