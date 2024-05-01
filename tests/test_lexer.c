#include "minishell.h"
#include <stdio.h>
#include <stdarg.h>

static t_token *create_with_enum(int num_args, ...)
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

int	ft_isequal(const char *a, const char *b)
{
	int idx = 0;

	while (a && b && a[idx] && b[idx])
	{
		if (a[idx] != b[idx])
			return (0);
		idx++;
	}
	return (1);
}

static int	is_equal(const t_token *a, const t_token *b)
{
	if (a == b)
		return (1);
	while (a != NULL && b != NULL)
	{
		if (a->type != b->type || a->lexema != b->lexema)
			return (0);
		a = a->next;
		b = b->next;
	}
	return (1);
}

static int	test_word_simple_quote()
{
	char	*word = "\'kjahsihsa dihhdakdha\'";
	t_token	*expected = NULL;
	t_token	*result;

	expected = malloc(sizeof(t_token));
	expected->lexema = "kjahsihsa dihhdakdha";
	expected->type = WORD;
	expected->next = NULL;
	result = lexer(word);
	return (ft_isequal(expected->lexema, result->lexema));
}

static int	test_symbols(void)
{
	char	*symbols = "    < && | >> << || $$ ( )";
	t_token	*expected;
	t_token	*result;

	expected = create_with_enum(10, REDIR_INPUT, AND, PIPE, OUTPUT_APPEND, HEREDOC, OR, DOLLAR, DOLLAR, L_PAREN, R_PAREN);
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
	if (!test_word_simple_quote())
	{
		printf("failed test_word_simple_quote\n");
		quit (EXIT_FAILURE);
	}
	quit (EXIT_SUCCESS);
}
