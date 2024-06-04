/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 08:19:03 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/04 19:07:53 by cnatanae         ###   ########.fr       */
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
	int		status;
	char	*username;
	t_envp	*my_envp;
	t_token	*token;
	t_token	*expr;

	(void)argc;
	(void)argv;
	expr = NULL;
	my_envp = create_envp(envp);
	while (1)
	{
		username = get_username(my_envp);
		line = readline(username);
		add_history(line);
		typetree_insert(line);
		token = lexer(line);
		if (line[0] == '\0' || token == NULL || syntax_error(token))
		{
			change_status(&my_envp, 2);
			line = readline(username);
			continue ;
		}
		expander_validation(&token, &my_envp);
		expr = cmd_parsing(token, &my_envp);
		if (syntax_expr(expr))
		{
			change_status(&my_envp, syntax_expr(expr));
			line = readline(username);
			continue ;
		}
		status = execute(expr, &my_envp);
		change_status(&my_envp, status);
	}
}

void	ending(int status)
{
	rl_clear_history();
	close(0);
	close(1);
	close(2);
	quit(status);
}
