/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:57:06 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/20 19:57:29 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file executor_utils.c
 * @brief This file contains the executor functions
 * @author @Chrystian-Natanael && @kellyhayd
*/

#include "minishell.h"

char	**separate_args(t_token *token)
{
	t_token	*tmp;
	char	**cmd;
	int		i;
	int		size_token;

	tmp = token;
	i = 0;
	size_token = 0;
	while (tmp)
	{
		tmp = tmp->next;
		size_token++;
	}
	cmd = (char **)allocate(sizeof(char *) * (size_token + 1));
	if (!cmd)
		return (NULL);
	tmp = token;
	while (tmp)
	{
		cmd[i] = ft_strdup(tmp->lexeme);
		typetree_insert(cmd[i++]);
		tmp = tmp->next;
	}
	cmd[i] = NULL;
	return (cmd);
}

int	verify_cmd(char **cmd)
{
	int	idx;

	if (cmd == NULL)
		return (0);
	idx = 0;
	while (cmd[idx])
	{
		if (verify_line(&cmd[idx]) == 0 && cmd[idx + 1] != NULL)
		{
			while (cmd[idx + 1])
			{
				cmd[idx] = cmd[idx + 1];
				idx++;
			}
			cmd[idx] = NULL;
			idx = 0;
			continue ;
		}
		else if (verify_line(&cmd[idx]) == 0)
			return (0);
		idx++;
	}
	return (1);
}
