#include "minishell.h"
#include <stdio.h>
#include <stdarg.h>

static t_token *create(int num_args, ...)
{
	t_token *result;
	va_list	ap;
	
	result = NULL;
	va_start(ap, num_args);
	while (num_args != 0)
	{
		lst_addnew(&result, va_arg(ap, enum e_token), NULL);
		num_args--;
	}
	va_end(ap);
	return (result);
}

static int	is_equal(const t_token *a, const t_token *b)
{
	if (a == b)
		return (1);
	while (a != NULL && b != NULL)
	{
		printf("%d %d \n", a->type, b->type);
		if (a->type != b->type || a->lexema != b->lexema)
			return (0);
		a = a->next;
		b = b->next;
	}
	return (a == b);
}

static int	test_symbols()
{
	char	*symbols = "    < && | >> << || $$ ( )";
	t_token	*expected;
	t_token	*result;

	expected = create(10, REDIR_INPUT, AND, PIPE, OUTPUT_APPEND, HEREDOC, OR, DOLLAR, DOLLAR, L_PAREN, R_PAREN);
	result = lexer(symbols);
	return (is_equal(expected, result));
}

static int	test_all_spaces_empty_list()
{
	char	*spaces = "       ";
	t_token	*expected = NULL;
	t_token	*result;

	result = lexer(spaces);
	return (is_equal(expected, result));
}

int	expr_is_equal(t_token *expected, t_token *result)
{
	while (expected != NULL && result != NULL)
	{
		if (expected->type != result->type || ft_strncmp(expected->lexema, result->lexema, ft_strlen(expected->lexema)))
			return (0);
		expected = expected->next;
		result = result->next;
	}
	return (expected == result);
}

static int	test_two_commands()
{
	//! line = "ls -l || echo hello";
	t_token	*expected;
	t_token	*result;
	t_token	*tokens;
	
	expected = create(2, EXPRESSION, EXPRESSION);
	expected->lexema = "ls -l";
	expected->next->lexema = "echo hello";
	tokens = create(5, WORD, WORD, OR, WORD, WORD);
	tokens->lexema = "ls";
	tokens->next->lexema = "-l";
	tokens->next->next->lexema = "||";
	tokens->next->next->next->lexema = "echo";
	tokens->next->next->next->next->lexema = "hello";
	result = cmd_parsing(tokens);
	return (expr_is_equal(expected, result));
}

int	main () {
	if (!test_all_spaces_empty_list())
	{
		printf("failed test_all_spaces_empty_list\n");
		quit (EXIT_FAILURE);
	}
	if (!test_symbols())
	{
		printf("failed test_symbols\n");
		quit (EXIT_FAILURE);
	}
	if(!test_two_commands())
	{
		printf("failed test_two_commands\n");
		quit (EXIT_FAILURE);
	}
	quit (EXIT_SUCCESS);
}