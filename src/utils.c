/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 19:50:30 by cnatanae          #+#    #+#             */
/*   Updated: 2024/05/01 09:28:44 by cnatanae         ###   ########.fr       */
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
	char	*str1;
	char	*str2;

	username = envp_get("USER", envp);
	if (!username)
		username = "minishell";
	str1 = ft_strjoin(username, "$: \033[0m");
	str2 = ft_strjoin("\033[92m", str1);
	typetree_insert(str1);
	typetree_insert(str2);
	return (str2);
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
