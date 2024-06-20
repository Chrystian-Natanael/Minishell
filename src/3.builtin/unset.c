/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:12:55 by krocha-h          #+#    #+#             */
/*   Updated: 2024/06/20 14:55:35 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file unset.c
 * @brief This file contains the unset function
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/05/31
*/

#include "minishell.h"

#include "minishell.h"

int	valid_var_export(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	i++;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	ft_unset(char **argv, t_envp **envp)
{
	t_envp	*prev;
	t_envp	*curr;
	int		var_name;
	int		exit_status;

	var_name = 1;
	exit_status = 0;
	if (!argv[1])
		return (0);
	while (argv[var_name])
	{
		curr = *envp;
		while (curr && ft_strcmp(argv[var_name], curr->key) != 0)
		{
			prev = curr;
			curr = curr->next;
		}
		if (curr && ft_strcmp(argv[var_name], curr->key) == 0)
		{
			if (curr == *envp)
				*envp = (*envp)->next;
			else
				prev->next = curr->next;
		}
		if (!valid_var_export(argv[var_name]))
			exit_status = ft_error("minishell: unset: '", argv[var_name], "': not a valid identifier", 1);
		var_name++;
	}
	return (exit_status);
}
