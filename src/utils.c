/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 19:50:30 by cnatanae          #+#    #+#             */
/*   Updated: 2024/05/01 11:17:56 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file utils.c
 * @brief This file contains the utils functions
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/04/27
*/

#include "minishell.h"

char	*get_username(t_envp *envp)
{
	char	*username;
	char	*final_string;
	char	*pwd;
	char	*str1;
	char	*str2;

	username = envp_get("USER", envp);
	pwd = envp_get("PWD", envp);
	if (!username)
		username = "minishell";
	str2 = ft_strrchr(pwd, '/');
	if (!str2)
		str2 = "//";
	str1 = ft_strjoin(++str2, "$\033[0m ");
	str2 = ft_strjoin("\033[92m", username);
	typetree_insert(str2);
	str2 = ft_strjoin(str2, "\033[0m:\033[34m");
	final_string = ft_strjoin(str2, str1);
	typetree_insert(final_string);
	typetree_insert(str2);
	typetree_insert(str1);
	return (final_string);
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

void	print_tokens(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		ft_printf("type: %d, lexema: %s\n", tmp->type, tmp->lexema);
		tmp = tmp->next;
	}
}