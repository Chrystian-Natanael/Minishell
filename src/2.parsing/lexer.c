/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 09:30:45 by krocha-h          #+#    #+#             */
/*   Updated: 2024/06/20 14:12:23 by cnatanae         ###   ########.fr       */
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

int	close_quote(char *line, int **i)
{
	int		size;
	char	type_quote;

	type_quote = line[(**i)++];
	size = 1;
	while (line[**i] && line[**i] != type_quote)
	{
		(**i)++;
		size++;
	}
	if (!line[**i] || line[**i] != type_quote)
		return (0);
	// size -= 1;
	return (size);
}

char	*get_word(char *line, int *i, int *state)
{
	int		tmp;
	int		idx;
	int		quote;
	char	*word;

	tmp = *i;
	idx = 0;
	while (line[*i] && !is_metacharacter(line[*i], line[(*i) + 1])
		&& !ft_isspace(line[*i]))
	{
		if (line[*i] == '\'' || line[*i] == '"')
			idx += close_quote(line, &i);
		idx++;
		(*i)++;
	}
	if (is_metacharacter(line[*i], 0))
		(*state)++;
	quote = quote_is_closed(line, i);
	if (quote == 0)
		return (NULL);
	word = allocate(sizeof(char) * (idx + 1));
	idx = 0;
	while (tmp < *i && line[tmp])
		word[idx++] = line[tmp++];
	word[idx] = '\0';
	return (word);
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

char	*get_token_word(char *line, int *i, int *type, int *state)
{
	char	*word;

	if (line[*i] == '\0')
		return (NULL);
	word = NULL;
	if (line[*i] == '"' || line[*i] == '\'')
		word = quote_word(line, i);
	else
		word = get_word(line, i, state);
	if (word)
		*type = WORD;
	return (word);
}

int	token_get_state_70(char character)
{
	int		i;
	int		state;
	int		token_type;
	char	*word;
	t_token	*list;

	i = 0;
	list = NULL;
	word = NULL;
	while (line && line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		token_type = get_token_type(line, i);
		state = 0;
		if (token_type >= OR || line[i] == ')')
		{
			if (token_type >= OR)
				i++;
			i++;
			state = 1;
		}
		if (token_type < 0)
			word = get_token_word(line, &i, &token_type, &state);
		if (token_type >= 0)
			lst_addnew(&list, token_type, word);
		word = NULL;
		if (line[i] != '\0' && line[i] != ')' && state == 0)
			i++;
	}
	return (list);
}
