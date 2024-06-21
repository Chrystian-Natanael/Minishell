/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 08:19:03 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/21 18:57:17 by krocha-h         ###   ########.fr       */
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
	tcgetattr(STDIN_FILENO, &data->term);
}

static void	reading_line(t_data *data)
{
	data->line = NULL;
	data->read_line = NULL;
	data->read_line = get_readline(data->my_envp, data);
	data->line = readline(data->read_line);
	if (g_sign == SIGINT)
	{
		data->status = 130;
		change_status(&data->my_envp, data->status);
	}
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

int	lexing(t_data *data)
{
	if (data->line == NULL)
	{
		data->line = ft_strdup("exit");
		typetree_insert(data->line);
	}
	if (!verify_line(&data->line))
	{
		change_status(&data->my_envp, 0);
		return (0);
	}
	data->token = lexer(data->line);
	g_sign = 0;
	heredoc_validation(&data);
	if (g_sign == SIGINT)
		return (0);
	if (data->token == NULL || data->line[0] == '\0'
		|| syntax_error(data->token) || quote_error(data->token))
	{
		change_status(&data->my_envp, 2);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	init_data(&data, argc, argv, envp);
	while (1)
	{
		init_signals();
		tcsetattr(STDIN_FILENO, TCSANOW, &data.term);
		reading_line(&data);
		if (!lexing(&data))
			continue ;
		data.expr = cmd_parsing(data.token, &data.my_envp);
		if (syntax_expr(data.expr))
		{
			change_status(&data.my_envp, 2);
			continue ;
		}
		data.status = execute(data.expr, &data);
		change_status(&data.my_envp, data.status);
	}
}
