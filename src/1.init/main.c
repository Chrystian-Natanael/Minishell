/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 08:19:03 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/20 12:33:02 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file main.c
 * @brief This file contains the main function
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/04/08
*/

#include "minishell.h"

int	g_sign;

static void	init_data(t_data *data, int argc, char **argv, char **envp);
static void	reading_line(t_data *data);

static void	init_data(t_data *data, int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	data->expr = NULL;
	data->my_envp = create_envp(envp);
	data->count_files = 0;
	data->status = 0;
	// loadingbar();
}

static void	reading_line(t_data *data)
{
	data->line = NULL;
	data->read_line = NULL;
	data->read_line = get_readline(data->my_envp, data);
	data->line = readline(data->read_line);
	if (data->line != NULL)
	{
		add_history(data->line);
		typetree_insert(data->line);
	}
}

int	verify_line(char **line)
{
	int	exist_line;
	int	size_line;
	int	idx;

	exist_line = 0;
	size_line = ft_strlen(*line);
	idx = 0;
	while (idx < size_line)
	{
		if (!ft_isspace((*line)[idx]))
			exist_line = 1;
		idx++;
	}
	return (exist_line);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	init_data(&data, argc, argv, envp);
	while (1)
	{
		init_signals();
		reading_line(&data);

		if (data.line == NULL)
			ending(data.status, &data) ;
		if (!verify_line(&data.line))
		{
			change_status(&data.my_envp, 0);
			continue ;
		}
		data.token = lexer(data.line);
		g_sign = 0;
		heredoc_validation(&data.token, &data.count_files);
		if (g_sign == SIGINT)
			continue ;
		if (data.token == NULL || data.line[0] == '\0'
			|| syntax_error(data.token) || quote_error(data.token))
		{
			change_status(&data.my_envp, 2);
			continue ;
		}
		data.expr = cmd_parsing(data.token, &data.my_envp);
		if (syntax_expr(data.expr))
		{
			change_status(&data.my_envp, syntax_expr(data.expr));
			continue ;
		}
		data.status = execute(data.expr, &data);
		change_status(&data.my_envp, data.status);
	}
}
