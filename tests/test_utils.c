/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 14:55:16 by krocha-h          #+#    #+#             */
/*   Updated: 2024/06/07 09:38:42 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

t_token *create_with_enum(int num_args, ...)
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

int	expr_is_equal(t_token *expected, t_token *result)
{
	while (expected != NULL && result != NULL)
	{
		if (expected->type != result->type || !is_equal_str(expected->lexema, result->lexema))
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

int	is_equal_str(const char *a, const char *b)
{
	int idx = 0;

	if (a && !b)
	{
		printf("\033[91m. \033[0m");
		return (0);
	}
	if (!a && b)
	{
		printf("\033[91m. \033[0m");
		return (0);
	}
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

int	is_equal(const t_token *a, const t_token *b)
{
	if (a == b)
	{
		printf("\033[92m. \033[0m");
		return (1);
	}
	while (a != NULL && b != NULL)
	{
		if (a->type != b->type || a->lexema != b->lexema)
		{
			printf("\033[91m. \033[0m");
			return (0);
		}
		a = a->next;
		b = b->next;
	}
	printf("\033[92m. \033[0m");
	return (1);
}