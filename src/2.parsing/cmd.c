/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:18:57 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/18 23:35:02 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file cmd.c
 * @brief This file contains the cmd functions
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/05/01
*/

#include "minishell.h"

t_token	*lstpickel(t_token *lst, int index)
{
	t_token	*el;
	t_token	*prev;

	if (!lst)
		return (NULL);
	else
	{
		el = lst;
		while (index--)
		{
			prev = el;
			el = el->next;
		}
		if (el == lst)
			lst = el->next;
		else
			prev->next = el->next;
	}
	return (el);
}
t_token	*lstpop(t_token *lst, int index)
{
	t_token	*el;

	el = lstpickel(lst, index);
	if (!el)
		return (NULL);
	el->next = NULL;
	return (el);
}

int	is_redirect(int	type)
{
	return (type == REDIR_INPUT || type == REDIR_OUTPUT
		|| type == OUTPUT_APPEND || type == HEREDOC);
}

int	count_redirects(t_token *token)
{
	int		count;
	t_token	*tmp;

	tmp = token;
	count = 0;
	while (tmp && (tmp->type == WORD || is_redirect(tmp->type)))
	{
		if (is_redirect(tmp->type))
			count++;
		tmp = tmp->next;
	}
	return (count);
}

void	organize_redirects(t_token **token)
{
	int		idx;
	int		odx;
	int		point;
	int		count_redir;
	t_token	*tmp;
	t_aux_redirect	**redir;

	tmp = *token;
	idx = 0;
	redir = NULL;
	while (tmp)
	{
		odx = 0;
		count_redir = 1;
		if (is_redirect(tmp->type) && tmp->next)
		{
			count_redir = count_redirects(tmp);
			redir = allocate(sizeof(t_token *) * (count_redir + 1));
			while (count_redir--)
			{
				redir[odx] = allocate(sizeof(t_aux_redirect));
				redir[odx]->redir = lstpop(*token, idx);
				redir[odx]->file_name = lstpop(*token, idx);
				tmp = *token;
				idx = 0;
				while ((tmp && !is_redirect(tmp->type) && count_redir) || idx < point)
				{
					tmp = tmp->next;
					idx++;
				}
				odx++;
			}
		}
		point = idx;
		if ((tmp->next && tmp->next->type != WORD && redir) || (!tmp->next && redir))
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
		if (tmp && (tmp->type == REDIR_INPUT || tmp->type == REDIR_OUTPUT
				|| tmp->type == OUTPUT_APPEND || tmp->type == HEREDOC))
		{
			cmd_parsing_aux(&head, &cmds, &tmp);
			lst_contatenate_redir(&cmds, tmp->lexeme);
			tmp = tmp->next;
		}
		else
		{
			while (tmp && tmp->type != PIPE && tmp->type != OR
				&& tmp->type != AND && tmp->type != L_PAREN
				&& tmp->type != R_PAREN && tmp->type != REDIR_INPUT
				&& tmp->type != REDIR_OUTPUT && tmp->type != OUTPUT_APPEND
				&& tmp->type != HEREDOC)
			{
				if ((tmp->lexeme && *tmp->lexeme != '\0') || tmp->type != WORD)
					lst_contatenate(&cmds, return_lexeme(tmp));
				tmp = tmp->next;
				if (!tmp)
					break ;
			}
		}
		cmd_parsing_aux(&head, &cmds, &tmp);
	}
	return (head);
}

char	*expan_get(t_token *token, t_envp *envp)
{
	t_envp	*current;

	current = envp;
	if (!token->lexeme)
		token->lexeme = return_lexeme(token);
	while (current)
	{
		if (ft_strncmp(current->key, token->lexeme, ft_strlen(token->lexeme)) == 0)
			return (current->value);
		current = current->next;
	}
	return ("");
}

void	cmd_parsing_aux(t_token **head, t_token **cmds, t_token **tmp)
{
	t_token	*aux;

	lstadd_back(head, *cmds);
	if (*cmds != NULL)
		*cmds = (*cmds)->next;
	if (*tmp && (((*tmp)->type == PIPE || (*tmp)->type == OR
				|| (*tmp)->type == AND) || (*tmp)->type == L_PAREN
			|| (*tmp)->type == R_PAREN || (*tmp)->type == REDIR_INPUT
			|| (*tmp)->type == REDIR_OUTPUT || (*tmp)->type == OUTPUT_APPEND
			|| (*tmp)->type == HEREDOC))
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
