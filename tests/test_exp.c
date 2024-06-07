/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_exp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 14:52:14 by krocha-h          #+#    #+#             */
/*   Updated: 2024/06/07 11:44:49 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	test_three_expr(t_envp **envp)
{
	//! line = "ls -l || echo hello";
	t_token	*expected;
	t_token	*result;
	t_token	*tokens;

	expected = create_with_enum(3, CMD, OR, CMD);
	expected->lexema = "ls -l";
	expected->next->lexema = "||";
	expected->next->next->lexema = "echo hello";
	tokens = create_with_enum(5, WORD, WORD, OR, WORD, WORD);
	tokens->lexema = "ls";
	tokens->next->lexema = "-l";
	tokens->next->next->lexema = "||";
	tokens->next->next->next->lexema = "echo";
	tokens->next->next->next->next->lexema = "hello";
	result = cmd_parsing(tokens, envp);
	return (expr_is_equal(expected, result));
}

int	test_five_expr(t_envp **envp)
{
	//! line = "ls -l | grep a >> outfile.txt && echo file created";
	t_token	*expected;
	t_token	*result;
	t_token	*tokens;

	expected = create_with_enum(7, CMD, PIPE, CMD, OUTPUT_APPEND, CMD, AND, CMD);
	expected->lexema = "ls -l";
	expected->next->lexema = "|";
	// expected->next->next->lexema = "grep a >> outfile.txt";
	expected->next->next->lexema = "grep a";
	expected->next->next->next->lexema = ">>";
	expected->next->next->next->next->lexema = "outfile.txt";
	expected->next->next->next->next->next->lexema = "&&";
	expected->next->next->next->next->next->next->lexema = "echo file created";
	tokens = create_with_enum(11, WORD, WORD, PIPE, WORD, WORD, OUTPUT_APPEND, WORD, AND, WORD, WORD, WORD);
	tokens->lexema = "ls";
	tokens->next->lexema = "-l";
	tokens->next->next->lexema = "|";
	tokens->next->next->next->lexema = "grep";
	tokens->next->next->next->next->lexema = "a";
	tokens->next->next->next->next->next->lexema = ">>";
	tokens->next->next->next->next->next->next->lexema = "outfile.txt";
	tokens->next->next->next->next->next->next->next->lexema = "&&";
	tokens->next->next->next->next->next->next->next->next->lexema = "echo";
	tokens->next->next->next->next->next->next->next->next->next->lexema = "file";
	tokens->next->next->next->next->next->next->next->next->next->next->lexema = "created";
	result = cmd_parsing(tokens, envp);
	return (expr_is_equal(expected, result));
}

int test_complex_expr(t_envp **envp)
{
	// ! "ls -la" | 'grep "a"' | "wc -l" >> 'outfile.txt' && "echo 'Deu bom'" || "echo 'Deu ruim'"
	t_token	*expected;
	t_token	*result;
	t_token	*tokens;

	expected = create_with_enum(11, CMD, PIPE, CMD, PIPE, CMD, OUTPUT_APPEND, CMD, AND, CMD, OR, CMD);
	expected->lexema = "\"ls -la\"";
	expected->next->lexema = "|";
	expected->next->next->lexema = "\'grep \"a\"\'";
	expected->next->next->next->lexema = "|";
	// expected->next->next->next->next->lexema = "\"wc -l\" >> \'outfile.txt\'";
	expected->next->next->next->next->lexema = "\"wc -l\"";
	expected->next->next->next->next->next->lexema = ">>";
	expected->next->next->next->next->next->next->lexema = "\'outfile.txt\'";
	expected->next->next->next->next->next->next->next->lexema = "&&";
	expected->next->next->next->next->next->next->next->next->lexema = "\"echo 'Deu bom'\"";
	expected->next->next->next->next->next->next->next->next->next->lexema = "||";
	expected->next->next->next->next->next->next->next->next->next->next->lexema = "\"echo 'Deu ruim'\"";
	tokens = lexer("\"ls -la\" | 'grep \"a\"' | \"wc -l\" >> 'outfile.txt' && \"echo 'Deu bom'\" || \"echo 'Deu ruim'\"");
	result = cmd_parsing(tokens, envp);
	return (expr_is_equal(expected, result));
}