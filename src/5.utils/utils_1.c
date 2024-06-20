/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 19:50:30 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/20 14:29:13 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file utils_1.c
 * @brief This file contains the utils functions
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/04/27
*/

#include "minishell.h"

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

void	lst_addnew(t_token **list, enum e_token type, char *lexeme)
{
	t_token	*new;
	t_token	*tmp;

	tmp = *list;
	new = allocate(sizeof(t_token));
	new->type = type;
	new->lexeme = lexeme;
	new->next = NULL;
	if (*list == NULL)
		*list = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	free_split(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	is_metacharacter(char a, char b)
{
	if (a == '|' || a == '(' || a == ')' || a == '<' || a == '>')
		return (1);
	else if (a == '&' && b == '&')
		return (1);
	return (0);
}

int	args_count(char **argv)
{
	int	count;

	count = 0;
	while (argv[count])
		count++;
	return (count);
}
