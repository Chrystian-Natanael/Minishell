/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 14:59:26 by krocha-h          #+#    #+#             */
/*   Updated: 2024/06/07 10:21:54 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	main (int	argc, char	**argv, char	**envp) {
	t_envp	*my_envp;

	(void)argc;
	(void)argv;
	my_envp = create_envp(envp);
	printf("\n\033[92mRunning tests simbols/expr/tokens...\033[0m\n");
	if (!test_all_spaces_empty_list())
		printf("\n\033[91mfailed test_all_spaces_empty_list\033[0m\n");
	if (!test_symbols())
		printf("\n\033[91mfailed test_symbols\033[0m\n");
	if (!test_word_simple_quote())
		printf("\n\033[91mfailed test_word_simple_quote\033[0m\n");
	if (!test_only_words_with_spaces())
		printf("\n\033[91mfailed test_only_words_with_spaces\033[0m\n");
	if (!test_words_with_metacharacters())
		printf("\n\033[91mfailed test_only_words_with_metacharacters\033[0m\n");
	if (!test_only_words_with_quotes_between())
		printf("\n\033[91mfailed test_only_words_with_quotes_between\033[0m\n");
	if(!test_three_expr(&my_envp))
		printf("\n\033[91mfailed test_three_expr\033[0m\n");
	if(!test_five_expr(&my_envp))
		printf("\n\033[91mfailed test_five_expr\033[0m\n");
	if (!test_complex_expr(&my_envp))
		printf("\n\033[91mfailed test_complex_expr\033[0m\n");

	// ! TESTES DE EXECUÇÃO
	printf("\n\n\033[92mRunning tests execution...\033[0m\n");

	if (!test_hello_world(&my_envp))
		printf("\n\033[91mfailed test_hello_world\033[0m\n");
	if (!test_echo_pipe(&my_envp))
		printf("\n\033[91mfailed test_echo_pipe\033[0m\n");
	// if (!test_echo_n(&my_envp))
	// 	printf("\n\033[91mfailed test_echo_n\033[0m\n");
	
	printf("\n");
	close(0);
	close(1);
	close(2);
	close(3);
	quit (EXIT_SUCCESS);
}
