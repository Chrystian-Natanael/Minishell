/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:41:15 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/03 09:04:16 by cnatanae         ###   ########.fr       */
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

	if (tmp->type == PIPE)
		return (ft_error("minishell", "syntax error near unexpected token ", return_lexema(tmp), 2));
	if (tmp->type == OR)
		return (ft_error("minishell", "syntax error near unexpected token ", return_lexema(tmp), 2));
	if (tmp->type == AND)
		return (ft_error("minishell", "syntax error near unexpected token ", return_lexema(tmp), 2));
	if (tmp->type == R_PAREN)
		return (ft_error("minishell", "syntax error near unexpected token ", return_lexema(tmp), 2));
	while (tmp)
	{
		if (tmp->type == PIPE && !tmp->next)
			return (ft_error("minishell", "syntax error near unexpected token ", return_lexema(tmp), 2));
		if (tmp->type == OR && !tmp->next)
			return (ft_error("minishell", "syntax error near unexpected token ", return_lexema(tmp), 2));
		if (tmp->type == AND && !tmp->next)
			return (ft_error("minishell", "syntax error near unexpected token ", return_lexema(tmp), 2));
		if (tmp->type == REDIR_INPUT && !tmp->next)
			return (ft_error("minishell", "syntax error near unexpected token ", return_lexema(tmp), 2));
		if (tmp->type == REDIR_OUTPUT && !tmp->next)
			return (ft_error("minishell", "syntax error near unexpected token ", return_lexema(tmp), 2));
		if (tmp->type == OUTPUT_APPEND && !tmp->next)
			return (ft_error("minishell", "syntax error near unexpected token ", return_lexema(tmp), 2));
		if (tmp->type == HEREDOC && !tmp->next)
			return (ft_error("minishell", "syntax error near unexpected token ", return_lexema(tmp), 2));
		if (tmp->type == L_PAREN && !tmp->next)
			return (ft_error("minishell", "syntax error near unexpected token ", return_lexema(tmp), 2));
		if (tmp->type == REDIR_INPUT && tmp->next->type != WORD)
			return (ft_error("minishell", "syntax error near unexpected token ", return_lexema(tmp), 2));
		if (tmp->type == REDIR_OUTPUT && tmp->next->type != WORD)
			return (ft_error("minishell", "syntax error near unexpected token ", return_lexema(tmp), 2));
		if (tmp->type == OUTPUT_APPEND && tmp->next->type != WORD)
			return (ft_error("minishell", "syntax error near unexpected token ", return_lexema(tmp), 2));
		if (tmp->type == HEREDOC && tmp->next->type != WORD)
			return (ft_error("minishell", "syntax error near unexpected token ", return_lexema(tmp), 2));
		if (tmp->type == PIPE && (tmp->next->type != WORD && tmp->next->type != L_PAREN))
			return (ft_error("minishell", "syntax error near unexpected token ", return_lexema(tmp), 2));
		if (tmp->type == OR && (tmp->next->type != WORD && tmp->next->type != L_PAREN))
			return (ft_error("minishell", "syntax error near unexpected token ", return_lexema(tmp), 2));
		if (tmp->type == AND && (tmp->next->type != WORD && tmp->next->type != L_PAREN))
			return (ft_error("minishell", "syntax error near unexpected token ", return_lexema(tmp), 2));
		tmp = tmp->next;
	}
	return (0);
}
