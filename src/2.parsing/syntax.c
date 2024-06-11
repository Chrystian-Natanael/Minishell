/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:41:15 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/11 15:08:04 by cnatanae         ###   ########.fr       */
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
	if (tmp->type == PIPE || tmp->type == OR || tmp->type == AND || tmp->type == R_PAREN)
		return (ft_error("minishell: ", "syntax error near unexpected token ", return_lexema(tmp), 2));
	while (tmp)
	{
		if (tmp->type == PIPE && !tmp->next)
			return (ft_error("minishell: ", "syntax error near unexpected token ", return_lexema(tmp), 2));
		if (tmp->type == OR && !tmp->next)
			return (ft_error("minishell: ", "syntax error near unexpected token ", return_lexema(tmp), 2));
		if (tmp->type == AND && !tmp->next)
			return (ft_error("minishell: ", "syntax error near unexpected token ", return_lexema(tmp), 2));
		if (tmp->type == REDIR_INPUT && !tmp->next)
			return (ft_error("minishell: ", "syntax error near unexpected token ", return_lexema(tmp), 2));
		if (tmp->type == REDIR_OUTPUT && !tmp->next)
			return (ft_error("minishell: ", "syntax error near unexpected token ", return_lexema(tmp), 2));
		if (tmp->type == OUTPUT_APPEND && !tmp->next)
			return (ft_error("minishell: ", "syntax error near unexpected token ", return_lexema(tmp), 2));
		if (tmp->type == HEREDOC && !tmp->next)
			return (ft_error("minishell: ", "syntax error near unexpected token ", return_lexema(tmp), 2));
		if (tmp->type == L_PAREN && !tmp->next)
			return (ft_error("minishell: ", "syntax error near unexpected token ", return_lexema(tmp), 2));
		if (tmp->type == REDIR_INPUT && (tmp->next->type != WORD && tmp->next->type != FILE_NAME))
			return (ft_error("minishell: ", "syntax error near unexpected token ", return_lexema(tmp), 2));
		if (tmp->type == REDIR_OUTPUT && tmp->next->type != WORD)
			return (ft_error("minishell: ", "syntax error near unexpected token ", return_lexema(tmp), 2));
		if (tmp->type == OUTPUT_APPEND && tmp->next->type != WORD)
			return (ft_error("minishell: ", "syntax error near unexpected token ", return_lexema(tmp), 2));
		if (tmp->type == HEREDOC && tmp->next->type != WORD)
			return (ft_error("minishell: ", "syntax error near unexpected token ", return_lexema(tmp), 2));
		if (tmp->type == PIPE && (tmp->next->type != WORD && tmp->next->type != L_PAREN))
			return (ft_error("minishell: ", "syntax error near unexpected token ", return_lexema(tmp), 2));
		if (tmp->type == OR && (tmp->next->type != WORD && tmp->next->type != L_PAREN))
			return (ft_error("minishell: ", "syntax error near unexpected token ", return_lexema(tmp), 2));
		if (tmp->type == AND && (tmp->next->type != WORD && tmp->next->type != L_PAREN && tmp->next->type != REDIR_INPUT))
			return (ft_error("minishell: ", "syntax error near unexpected token ", return_lexema(tmp), 2));
		tmp = tmp->next;
	}
	return (0);
}

int	syntax_expr(t_token *expr)
{
	t_token	*tmp;

	tmp = expr;
	if (!tmp)
		return (ft_error("minishell: ", "syntax error near unexpected token ", return_lexema(tmp), 2));
	while (tmp)
	{
		if (tmp->type == R_PAREN)
			return (ft_error("minishell: ", "syntax error near unexpected token ", return_lexema(tmp), 2));
		tmp = tmp->next;
	}
	return (0);
}

int	quote_error(t_token *tokens)
{
	t_token	*tmp;
	char	quote_type;
	int		i;

	tmp = tokens;
	while (tmp)
	{
		i = 0;
		while (tmp->lexema && tmp->lexema[i])
		{
			if (tmp->lexema[i] == '"' || tmp->lexema[i] == '\'')
			{
				quote_type = tmp->lexema[i++];
				while (tmp->lexema[i] && tmp->lexema[i] != quote_type)
					i++;
				if (!tmp->lexema[i])
					return (1);
			}
			i++;
		}
		tmp = tmp->next;
	}
	return (0);
}
