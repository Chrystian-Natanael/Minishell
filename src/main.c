/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 08:19:03 by cnatanae          #+#    #+#             */
/*   Updated: 2024/05/10 11:40:36 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file main.c
 * @brief This file contains the main function
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/04/08
*/

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	*username;
	t_envp	*my_envp;
	t_token	*token;
	t_token	*expr;

	(void)argc;
	(void)argv;
	my_envp = create_envp(envp);
	username = get_username(my_envp);
	while ((line = readline(username))) // ! Não pode fazer isso segundo a norminette ;-;
	{
		username = get_username(my_envp);
		if (line[0] != '\0')
			add_history(line);
		typetree_insert(line);
		token = lexer(line);
		if (token == NULL)
		{
			ft_printf("\033[91mError: \033[0mInvalid syntax\n");
			continue ;
		}
		expr = cmd_parsing(token);
		// print_tokens(token);
		print_tokens(expr);
		// execute(expr, my_envp);
	}
	rl_clear_history();
	ft_printf("\033[91mEnding Minishell\033[0m, \033[92mThanks!\033[0m\n");
	quit(0);
}
