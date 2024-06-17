/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 09:30:45 by krocha-h          #+#    #+#             */
/*   Updated: 2024/06/17 15:03:46 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file lexer.c
 * @brief This file contains the lexer functions
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/05/01
*/

#include "minishell.h"

t_token	*lexer(char *line)
{
	t_token	*list;
	t_aux_token	aux;

	ft_bzero(&aux, sizeof(t_aux_token));
	aux.state = 1;
	aux.str_length = ft_strlen(line);
	list = NULL;
	while (aux.i <= aux.str_length)
	{
		aux.state = get_next_state(aux.state, line[aux.i]);
		if (aux.state != 1)
			aux.lexeme_length++;
		if (aux.state == -1)
			break ;
		if (state_is_final(aux.state))
			aux_state_final(&aux, line, &list);
		aux.i++;
	}
	return (list);
}

int	get_next_state(int state, char character)
{
	int	new_state;

	if (state == 1)
		new_state = token_get_state_1(character);
	else if (state == 40)
		new_state = token_get_state_40(character);
	else if (state == 50)
		new_state = token_get_state_50(character);
	else if (state == 60)
		new_state = token_get_state_60(character);
	else if (state == 70)
		new_state = token_get_state_70(character);
	else if (state == 80)
		new_state = token_get_state_80(character);
	else if (state == 81)
		new_state = token_get_state_81(character);
	else if (state == 82)
		new_state = token_get_state_82(character);
	else
		new_state = -1;
	return (new_state);
}

int	state_is_final(int state)
{
	if (state == 20
		|| state == 30
		|| state == 41 || state == 42
		|| state == 51
		|| state == 61 || state == 62
		|| state == 71 || state == 72
		|| state == 83)
		return (1);
	return (0);
}

void	aux_state_final(t_aux_token *aux, char *str, \
		t_token **token_list)
{
	if (state_require_backtrack(aux->state))
	{
		aux->i -= 1;
		aux->lexeme_length -= 1;
	}
	aux->token_type = token_get_token_type(aux->state);
	if (aux->token_type == WORD)
	{
		aux->lexeme = ft_substr(str, aux->i - (aux->lexeme_length - 1), \
		aux->lexeme_length);
		typetree_insert(aux->lexeme);
	}
	else
		aux->lexeme = NULL;
	token_add_to_list(token_list, aux->lexeme, aux->token_type);
	aux->lexeme_length = 0;
	aux->state = 1;
}

int	state_require_backtrack(int state)
{
	if (state == 42
		|| state == 62
		|| state == 72
		|| state == 83)
		return (1);
	return (0);
}

int	token_get_token_type(int state)
{
	int	type;

	if (state == 20)
		type = L_PAREN;
	else if (state == 30)
		type = R_PAREN;
	else if (state == 41)
		type = OR;
	else if (state == 42)
		type = PIPE;
	else if (state == 51)
		type = AND;
	else if (state == 61)
		type = HEREDOC;
	else if (state == 62)
		type = REDIR_INPUT;
	else if (state == 71)
		type = OUTPUT_APPEND;
	else if (state == 72)
		type = REDIR_OUTPUT;
	else if (state == 83)
		type = WORD;
	else
		type = -1;
	return (type);
}

t_token	*token_create_node(char *lexema, int token_type)
{
	t_token	*new_token;

	new_token = allocate(sizeof(t_token));
	new_token->lexema = lexema;
	new_token->type = token_type;
	new_token->next = NULL;
	return (new_token);
}

void	token_add_to_list(t_token **tok_lst, char *lex, int token_type)
{
	t_token	*new_token;
	t_token	*last_node;

	new_token = token_create_node(lex, token_type);
	last_node = *tok_lst;
	while (last_node && last_node->next)
		last_node = last_node->next;
	if (last_node)
		last_node->next = new_token;
	else
		*tok_lst = new_token;
}

// ! ----------------------------------------------------------------------------------

int	token_get_state_1(char character)
{
	int	state;

	if (character == '(')
		state = 20;
	else if (character == ')')
		state = 30;
	else if (character == '|')
		state = 40;
	else if (character == '&')
		state = 50;
	else if (character == '<')
		state = 60;
	else if (character == '>')
		state = 70;
	else if (character == '\'')
		state = 81;
	else if (character == '\"')
		state = 82;
	else if (character == '\0' || ft_isspace(character))
		state = 1;
	else if (is_metacharacter_char(character) == 0)
		state = 80;
	else
		state = -1;
	return (state);
}

int	token_get_state_40(char character)
{
	int	state;

	if (character == '|')
		state = 41;
	else if (character != '|')
		state = 42;
	else
		state = -1;
	return (state);
}

int	token_get_state_50(char character)
{
	int	state;

	if (character == '&')
		state = 51;
	else if (character != '&')
		state = -1;
	else
		state = -1;
	return (state);
}

int	token_get_state_60(char character)
{
	int	state;

	if (character == '<')
		state = 61;
	else if (character != '<')
		state = 62;
	else
		state = -1;
	return (state);
}

int	token_get_state_70(char character)
{
	int	state;

	if (character == '>')
		state = 71;
	else if (character != '>')
		state = 72;
	else
		state = -1;
	return (state);
}

int	token_get_state_80(char character)
{
	int	state;

	if (character == '\'')
		state = 81;
	else if (character == '\"')
		state = 82;
	else if (is_metacharacter_char(character) == 1 || character == '\0')
		state = 83;
	else if (is_metacharacter_char(character) == 0)
		state = 80;
	else
		state = -1;
	return (state);
}

int	token_get_state_81(char character)
{
	int	state;

	if (character == '\0')
		state = -1;
	else if (character == '\'')
		state = 80;
	else if (character != '\'')
		state = 81;
	else
		state = -1;
	return (state);
}

int	token_get_state_82(char character)
{
	int	state;

	if (character == '\0')
		state = -1;
	else if (character == '\"')
		state = 80;
	else if (character != '\"')
		state = 82;
	else
		state = -1;
	return (state);
}




int	is_metacharacter_char(char character)
{
	if (character == '('
		|| character == ')'
		|| character == '|'
		|| character == '&'
		|| character == '<'
		|| character == '>'
		|| character == '\''
		|| character == '\"'
		|| ft_isspace(character))
		return (1);
	return (0);
}
