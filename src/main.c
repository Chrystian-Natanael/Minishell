/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 08:19:03 by cnatanae          #+#    #+#             */
/*   Updated: 2024/05/01 08:39:06 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	main(void)
{
	char	*line;
	t_token	*token;

	ft_printf("\033[92mWelcome to Minishell, enjoy! \033[0m\n");
	line = readline("\033[94mminishell$: \033[0m");
	while (line)
	{
		if (line[0] != '\0')
			add_history(line);
		typetree_insert(line);
		line = readline("\033[94mminishell$: \033[0m");
		token = lexer(line);
		print_tokens(token);
	}
	rl_clear_history();
	ft_printf("\033[91mEnding Minishell\033[0m, \033[92mThanks!\033[0m\n");
	quit(0);
}
