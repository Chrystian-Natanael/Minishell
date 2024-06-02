/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:41:15 by cnatanae          #+#    #+#             */
/*   Updated: 2024/05/16 13:14:50 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file syntax.c
 * @brief This file contains the syntax functions
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/05/10
*/

#include "minishell.h"

int	syntax_error(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (!tmp)
		return (1);
	if (tmp->type == PIPE)
		return (1);
	if (tmp->type == OR)
		return (1);
	if (tmp->type == AND)
		return (1);
	while (tmp)
	{
		if (tmp->type == PIPE && !tmp->next)
			return (1);
		if (tmp->type == OR && !tmp->next)
			return (1);
		if (tmp->type == AND && !tmp->next)
			return (1);
		if (tmp->type == REDIR_INPUT && !tmp->next)
			return (1);
		if (tmp->type == REDIR_OUTPUT && !tmp->next)
			return (1);
		if (tmp->type == OUTPUT_APPEND && !tmp->next)
			return (1);
		if (tmp->type == HEREDOC && !tmp->next)
			return (1);
		if (tmp->type == L_PAREN && !tmp->next)
			return (1);
		if (tmp->type == REDIR_INPUT && tmp->next->type != WORD)
			return (1);
		if (tmp->type == REDIR_OUTPUT && tmp->next->type != WORD)
			return (1);
		if (tmp->type == OUTPUT_APPEND && tmp->next->type != WORD)
			return (1);
		if (tmp->type == HEREDOC && tmp->next->type != WORD)
			return (1);
		if (tmp->type == PIPE && (tmp->next->type != WORD && tmp->next->type != L_PAREN))
			return (1);
		if (tmp->type == OR && (tmp->next->type != WORD && tmp->next->type != L_PAREN))
			return (1);
		if (tmp->type == AND && (tmp->next->type != WORD && tmp->next->type != L_PAREN))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}