/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 19:17:53 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/21 22:04:20 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file cmd_utils.c
 * @brief This file contains the lst functions
 * @author @Chrystian-Natanael
 * @date 2024/06/21
*/

#include "minishell.h"

t_token	*lstpickel(t_token **lst, int index)
{
	t_token	*el;
	t_token	*prev;

	if (!lst || !(*lst))
		return (NULL);
	else
	{
		el = *lst;
		while (index--)
		{
			prev = el;
			el = el->next;
		}
		if (el == *lst)
			*lst = el->next;
		else
			prev->next = el->next;
	}
	return (el);
}

t_token	*lstpop(t_token **lst, int index)
{
	t_token	*el;

	el = lstpickel(lst, index);
	if (!el)
		return (NULL);
	el->next = NULL;
	return (el);
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

char	*expan_get(t_token *token, t_envp *envp)
{
	t_envp	*current;

	current = envp;
	if (!token->lexeme)
		token->lexeme = return_lexeme(token);
	while (current)
	{
		if (ft_strncmp(current->key, token->lexeme, \
		ft_strlen(token->lexeme)) == 0)
			return (current->value);
		current = current->next;
	}
	return ("");
}
