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
	char	*symbols = "    < && | > << || $ ( )";
	t_token	*expected;
	t_token	*result;

	expected = create(9, REDIR_INPUT, AND, PIPE, REDIR_OUTPUT, HEREDOC, OR, DOLLAR, L_PAREN, R_PAREN);
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
		return (EXIT_FAILURE);
	}
	if (!test_symbols())
	{
		printf("failed test_symbols\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}