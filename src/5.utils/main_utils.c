/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:43:56 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/21 20:45:05 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This file cotains functions utils
 * @author @Chrystian-Natanael
 * @date 2024/06/10
*/

char	*get_readline(t_envp *envp, t_data *data)
{
	char	*final_string;
	char	*pwd;
	char	*str1;
	char	cwd[PATH_MAX];

	pwd = NULL;
	data->read_line = envp_get("USER", envp);
	if (getcwd(cwd, PATH_MAX))
		pwd = ft_strdup(cwd);
	if (!data->read_line)
		data->read_line = "minishell";
	data->line = ft_strrchr(pwd, '/');
	if (!data->line)
		data->line = "//";
	str1 = ft_strjoin(++data->line, " $\033[0m ");
	data->line = ft_strjoin("\033[92m", data->read_line);
	typetree_insert(data->line);
	typetree_insert(pwd);
	data->line = ft_strjoin(data->line, "\033[0m:\033[34m");
	final_string = ft_strjoin(data->line, str1);
	typetree_insert(final_string);
	typetree_insert(data->line);
	typetree_insert(str1);
	return (final_string);
}

void	ending(int status)
{
	rl_clear_history();
	close(0);
	close(1);
	close(2);
	close(3);
	quit(status);
}
