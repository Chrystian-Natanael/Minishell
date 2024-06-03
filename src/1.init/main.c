/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 08:19:03 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/03 15:26:40 by cnatanae         ###   ########.fr       */
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
	expr = NULL;
	my_envp = create_envp(envp);
	username = get_username(my_envp);
	line = readline(username);
	while ((line))
	{
		username = get_username(my_envp);
		typetree_insert(line);
		token = lexer(line);
		if (line[0] == '\0' || token == NULL || syntax_error(token))
		{
			line = readline(username);
			continue ;
		}
		add_history(line);
		expr = cmd_parsing(token);
		if (expr == NULL)
		{
			ft_error("minishell: syntax error", "", "", 2);
			line = readline(username);
			continue ;
		}
		(void)execute(expr, &my_envp);
		line = readline(username);
	}
	ft_printf("\033[91mEnding Minishell\033[0m, \033[92mThanks!\033[0m\n");
	ending(0);
}

void	ending(int status)
{
	rl_clear_history();
	close(0);
	close(1);
	close(2);
	quit(status);
}
