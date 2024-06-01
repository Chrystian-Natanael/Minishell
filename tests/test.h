/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 14:56:02 by krocha-h          #+#    #+#             */
/*   Updated: 2024/06/01 15:14:22 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <stdarg.h>

#include "minishell.h"

t_token *create_with_enum(int num_args, ...);
int	expr_is_equal(t_token *expected, t_token *result);
int	is_equal_str(const char *a, const char *b);
int	is_equal(const t_token *a, const t_token *b);
int	test_only_words_with_quotes_between();
int	test_words_with_metacharacters();
int	test_only_words_with_spaces();
int	test_word_simple_quote();
int	test_symbols(void);
int	test_all_spaces_empty_list();
int	test_three_expr();
int	test_five_expr();
int test_complex_expr();
int	test_pwd();

#endif