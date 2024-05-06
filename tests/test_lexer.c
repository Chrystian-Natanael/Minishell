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
		{
			printf("\033[91m. \033[0m");
			return (0);
		}
		idx++;
	}
	printf("\033[92m. \033[0m");
	return (1);
}

static int	is_equal(const t_token *a, const t_token *b)
{
	if (a == b)
	{
		printf("\033[92m. \033[0m");
		return (1);
	}
	while (a != NULL && b != NULL)
	{
		// printf("%d %d \n", a->type, b->type);
		if (a->type != b->type || a->lexema != b->lexema)
		{
			printf("\033[91m. \033[0m");
			return (0);
		}
		a = a->next;
		b = b->next;
	}
	printf("\033[92m. \033[0m");
	// return (a == b);
	return (1);
}

static int	test_word_simple_quote()
{
	char	*word = "\'kjahsihsa dihhdakdha\'";
	t_token	*expected = NULL;
	t_token	*result;

	expected = allocate(sizeof(t_token));
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

int	expr_is_equal(t_token *expected, t_token *result)
{
	while (expected != NULL && result != NULL)
	{
		if (expected->type != result->type || ft_strncmp(expected->lexema, result->lexema, ft_strlen(expected->lexema)))
		{
			printf("\033[91m. \033[0m");
			return (0);
		}
		expected = expected->next;
		result = result->next;
	}
	printf("\033[92m. \033[0m");
	return (expected == result);
}

static int	test_three_expr()
{
	//! line = "ls -l || echo hello";
	t_token	*expected;
	t_token	*result;
	t_token	*tokens;
	
	expected = create_with_enum(3, EXPRESSION, OR, EXPRESSION);
	expected->lexema = "ls -l";
	expected->next->lexema = "||";
	expected->next->next->lexema = "echo hello";
	tokens = create_with_enum(5, WORD, WORD, OR, WORD, WORD);
	tokens->lexema = "ls";
	tokens->next->lexema = "-l";
	tokens->next->next->lexema = "||";
	tokens->next->next->next->lexema = "echo";
	tokens->next->next->next->next->lexema = "hello";
	result = cmd_parsing(tokens);
	return (expr_is_equal(expected, result));
}

static int	test_five_expr()
{
	//! line = "ls -l | grep a >> outfile.txt && echo file created";
	t_token	*expected;
	t_token	*result;
	t_token	*tokens;

	expected = create_with_enum(5, EXPRESSION, PIPE, EXPRESSION, AND, EXPRESSION);
	expected->lexema = "ls -l";
	expected->next->lexema = "|";
	expected->next->next->lexema = "grep a >> outfile.txt";
	expected->next->next->next->lexema = "&&";
	expected->next->next->next->next->lexema = "echo file created";
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
	result = cmd_parsing(tokens);
	return (expr_is_equal(expected, result));
}

static int test_complex_expr()
{
	// ! "ls -la" | 'grep "a"' | "wc -l" >> 'outfile.txt' && "echo 'Deu bom'" || "echo 'Deu ruim'"
	t_token	*expected;
	t_token	*result;
	t_token	*tokens;

	expected = create_with_enum(9, EXPRESSION, PIPE, EXPRESSION, PIPE, EXPRESSION, AND, EXPRESSION, OR, EXPRESSION);
	expected->lexema = "ls -la";
	expected->next->lexema = "|";
	expected->next->next->lexema = "grep \"a\"";
	expected->next->next->next->lexema = "|";
	expected->next->next->next->next->lexema = "wc -l >> outfile.txt";
	expected->next->next->next->next->next->lexema = "&&";
	expected->next->next->next->next->next->next->lexema = "echo 'Deu bom'";
	expected->next->next->next->next->next->next->next->lexema = "||";
	expected->next->next->next->next->next->next->next->next->lexema = "echo 'Deu ruim'";
	tokens = lexer("\"ls -la\" | 'grep \"a\"' | \"wc -l\" >> 'outfile.txt' && \"echo 'Deu bom'\" || \"echo 'Deu ruim'\"");
	result = cmd_parsing(tokens);
	return (expr_is_equal(expected, result));
}

int	main () {
	if (!test_all_spaces_empty_list())
	{
		printf("\033[91mfailed test_all_spaces_empty_list\033[0m\n");
		quit (EXIT_FAILURE);
	}
	if (!test_symbols())
	{
		printf("\033[91mfailed test_symbols\033[0m\n");
		quit (EXIT_FAILURE);
	}
	if(!test_three_expr())
	{
		printf("\033[91mfailed test_three_expr\033[0m\n");
		quit (EXIT_FAILURE);
	}
	if(!test_five_expr())
	{
		printf("\033[91mfailed test_five_expr\033[0m\n");
		quit (EXIT_FAILURE);
	}
	if (!test_word_simple_quote())
	{
		printf("\033[91mfailed test_word_simple_quote\033[0m\n");
		quit (EXIT_FAILURE);
	}
	if (!test_complex_expr())
	{
		printf("\033[91mfailed test_complex_expr\033[0m\n");
		quit (EXIT_FAILURE);
	}
	printf("\n\n\033[92mAll tests passed\033[0m\n");
	quit (EXIT_SUCCESS);
}
