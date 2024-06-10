/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 08:19:03 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/10 12:11:45 by cnatanae         ###   ########.fr       */
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
	loadingBar();
	while (1)
	{
		username = get_username(my_envp);
		line = readline(username);
		add_history(line);
		typetree_insert(line);
		token = lexer(line);
		heredoc_validation(&token);
		if (line[0] == '\0' || token == NULL || syntax_error(token))
		{
			change_status(&my_envp, 2);
			continue ;
		}
		expander_validation(&token, &my_envp);
		expr = cmd_parsing(token, &my_envp);
		if (syntax_expr(expr))
		{
			change_status(&my_envp, syntax_expr(expr));
			continue ;
		}
		status = execute(expr, &my_envp);
		change_status(&my_envp, status);
	}
}

