/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:12:55 by krocha-h          #+#    #+#             */
/*   Updated: 2024/06/02 17:01:33 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file pwd.c
 * @brief This file contains the pwd function
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/05/31
*/

#include "minishell.h"

int	ft_unset(char **argv, t_envp **envp)
{
	t_envp	*prev;
	t_envp	*curr;

	if (!argv[1])
		return (0);
	curr = *envp;
	while (curr && ft_strcmp(argv[1], curr->key) != 0)
	{
		prev = curr;
		curr = curr->next;
	}
	if (ft_strcmp(argv[1], curr->key) == 0)
	{
		if (curr == *envp)
			*envp = (*envp)->next;
		else
			prev->next = curr->next;
		deallocate(curr);
	}
	return (0);
}
