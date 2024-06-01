/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 14:59:26 by krocha-h          #+#    #+#             */
/*   Updated: 2024/06/01 15:39:16 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	main () {
	if (!test_all_spaces_empty_list())
	{
		printf("\n\033[91mfailed test_all_spaces_empty_list\033[0m\n");
		// quit (EXIT_FAILURE);
	}
	if (!test_symbols())
	{
		printf("\n\033[91mfailed test_symbols\033[0m\n");
		// quit (EXIT_FAILURE);
	}
	if (!test_word_simple_quote())
	{
		printf("\n\033[91mfailed test_word_simple_quote\033[0m\n");
		// quit (EXIT_FAILURE);
	}
	if (!test_only_words_with_spaces())
	{
		printf("\n\033[91mfailed test_only_words_with_spaces\033[0m\n");
		// quit (EXIT_FAILURE);
	}
	if (!test_words_with_metacharacters())
	{
		printf("\n\033[91mfailed test_only_words_with_metacharacters\033[0m\n");
		// quit (EXIT_FAILURE);
	}
	if (!test_only_words_with_quotes_between())
	{
		printf("\n\033[91mfailed test_only_words_with_quotes_between\033[0m\n");
		// quit (EXIT_FAILURE);
	}
	if(!test_three_expr())
	{
		printf("\n\033[91mfailed test_three_expr\033[0m\n");
		// quit (EXIT_FAILURE);
	}
	if(!test_five_expr())
	{
		printf("\n\033[91mfailed test_five_expr\033[0m\n");
		// quit (EXIT_FAILURE);
	}
	if (!test_complex_expr())
	{
		printf("\n\033[91mfailed test_complex_expr\033[0m\n");
		// quit (EXIT_FAILURE);
	}
	if (!test_pwd())
	{
		printf("\n\033[91mfailed test_pwd\033[0m\n");
		// quit (EXIT_FAILURE);	
	}
	// printf("\n\n\033[92mAll tests passed\033[0m\n");
	printf("\n");
	quit (EXIT_SUCCESS);
}
