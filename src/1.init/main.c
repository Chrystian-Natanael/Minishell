/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 08:19:03 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/10 12:46:16 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file main.c
 * @brief This file contains the main function
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/04/08
*/

#include "minishell.h"

static void	init_data(t_data *data, int argc, char **argv, char **envp);
static void	reading_line(t_data *data);

static void	init_data(t_data *data, int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	data->expr = NULL;
	data->my_envp = create_envp(envp);
	data->count_files = 0;
	loadingBar();
}

static void	reading_line(t_data *data)
{
	data->read_line = get_readline(data->my_envp);
	data->line = readline(data->read_line);
	add_history(data->line);
	typetree_insert(data->line);	
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	init_data(&data, argc, argv, envp);
	while (1)
	{
		reading_line(&data);
		data.token = lexer(data.line);
		heredoc_validation(&data.token, &data.count_files);
		if (data.line[0] == '\0' || data.token == NULL
			|| syntax_error(data.token))
		{
			change_status(&data.my_envp, 2);
			continue ;
		}
		expander_validation(&data.token, &data.my_envp);
		data.expr = cmd_parsing(data.token, &data.my_envp);
		if (syntax_expr(data.expr))
		{
			change_status(&data.my_envp, syntax_expr(data.expr));
			continue ;
		}
		data.status = execute(data.expr, &data.my_envp, &data);
		change_status(&data.my_envp, data.status);
	}
}

