/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:41:15 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/21 13:09:36 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file syntax.c
 * @brief This file contains the syntax functions
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/05/10
*/

#include "minishell.h"

int	is_missing_token(t_token *token)
{
	return (!token->next && (
			token->type == PIPE
			|| token->type == OR
			|| token->type == AND
			|| token->type == REDIR_INPUT
			|| token->type == REDIR_OUTPUT
			|| token->type == OUTPUT_APPEND
			|| token->type == HEREDOC
			|| token->type == L_PAREN));
}

int	is_wrong_combination_of_tokens(t_token *token)
{
	return (token->next && (
			(token->type == REDIR_INPUT && token->next->type != WORD
				&& token->next->type != FILE_NAME)
			|| (token->type == REDIR_OUTPUT && token->next->type != WORD)
			|| (token->type == OUTPUT_APPEND && token->next->type != WORD)
			|| (token->type == HEREDOC && token->next->type != WORD)
			|| (token->type == OR && token->next->type != WORD
				&& token->next->type != L_PAREN)
			|| (token->type == AND && token->next->type != WORD
				&& token->next->type != L_PAREN
				&& token->next->type != REDIR_INPUT)));
}

int	syntax_error(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (tmp->type == PIPE || tmp->type == OR || tmp->type == AND
		|| tmp->type == R_PAREN)
		return (ft_error("minishell: ", "syntax error near unexpected\
			 token ", return_lexeme(tmp), 2));
	while (tmp)
	{
		if (is_missing_token(token) || is_wrong_combination_of_tokens(token))
			return (ft_error("minishell: ", "syntax error near unexpected\
				token ", return_lexeme(token), 2));
		tmp = tmp->next;
	}
	return (0);
}

int	syntax_expr(t_token *expr)
{
	t_token	*tmp;

	tmp = expr;
	if (!tmp)
		return (ft_error("minishell: ", "syntax error near unexpected\
			 token ", return_lexeme(tmp), 2));
	while (tmp)
	{
		if (tmp->type == R_PAREN)
			return (ft_error("minishell: ", "syntax error near unexpected\
				 token ", return_lexeme(tmp), 2));
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
		while (tmp->lexeme && tmp->lexeme[i])
		{
			if (tmp->lexeme[i] == '"' || tmp->lexeme[i] == '\'')
			{
				quote_type = tmp->lexeme[i++];
				while (tmp->lexeme[i] && tmp->lexeme[i] != quote_type)
					i++;
				if (!tmp->lexeme[i])
					return (1);
			}
			i++;
		}
		tmp = tmp->next;
	}
	return (0);
}
