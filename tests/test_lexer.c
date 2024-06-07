/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 14:18:31 by krocha-h          #+#    #+#             */
/*   Updated: 2024/06/07 08:17:59 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

// static int	test_quotes_not_closed()
// {
// 	char	*word = "texto com \'aspas abertas";
// 	t_token	*expected = NULL;
// 	t_token	*result;

// 	expected = create_with_enum(5, WORD, WORD, WORD, WORD, WORD);

// }

int	test_only_words_with_quotes_between()
{
	char	*word = "as\"pas\" no meio da pa\'la\'vra";
	t_token	*expected = NULL;
	t_token	*result;

	expected = create_with_enum(5, WORD, WORD, WORD, WORD, WORD);
	expected->lexema = "aspas";
	expected->next->lexema = "no";
	expected->next->next->lexema = "meio";
	expected->next->next->next->lexema = "da";
	expected->next->next->next->next->lexema = "pa\'la\'vra";
	result = lexer(word);
	return (expr_is_equal(expected, result));
}

int	test_words_with_metacharacters()
{
	char	*word = "palavras >> com && meta | caractere";
	t_token	*expected = NULL;
	t_token	*result;

	expected = create_with_enum(7, WORD, OUTPUT_APPEND, WORD, AND, WORD, PIPE, WORD);
	expected->lexema = "palavras";
	expected->next->lexema = NULL;
	expected->next->next->lexema = "com";
	expected->next->next->next->lexema = NULL;
	expected->next->next->next->next->lexema = "meta";
	expected->next->next->next->next->next->lexema = NULL;
	expected->next->next->next->next->next->next->lexema = "caractere";
	result = lexer(word);
	return (expr_is_equal(expected, result));
}

int	test_only_words_with_spaces()
{
	char	*word = "teste de palavras com espacos";
	t_token	*expected = NULL;
	t_token	*result;

	expected = create_with_enum(5, WORD, WORD, WORD, WORD, WORD);
	expected->lexema = "teste";
	expected->next->lexema = "de";
	expected->next->next->lexema = "palavras";
	expected->next->next->next->lexema = "com";
	expected->next->next->next->next->lexema = "espacos";
	result = lexer(word);
	return (expr_is_equal(expected, result));
}

int	test_word_simple_quote()
{
	char	*word = "\'kjahsihsa dihhdakdha\'";
	t_token	*expected = NULL;
	t_token	*result;

	expected = allocate(sizeof(t_token));
	expected->lexema = "\'kjahsihsa dihhdakdha\'";
	expected->type = WORD;
	expected->next = NULL;
	result = lexer(word);
	return (is_equal_str(expected->lexema, result->lexema));
}

int	test_symbols(void)
{
	char	*symbols = "    < && | >> << ||  ( )";
	t_token	*expected;
	t_token	*result;

	expected = create_with_enum(9, REDIR_INPUT, AND, PIPE, OUTPUT_APPEND, HEREDOC, OR, L_PAREN, R_PAREN);
	result = lexer(symbols);
	return (is_equal(expected, result));
}

int	test_all_spaces_empty_list()
{
	char	*spaces = "       ";
	t_token	*expected = NULL;
	t_token	*result;

	result = lexer(spaces);
	return (is_equal(expected, result));
}