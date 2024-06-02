/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:12:55 by krocha-h          #+#    #+#             */
/*   Updated: 2024/06/01 21:25:43 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file pwd.c
 * @brief This file contains the pwd function
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/05/31
*/

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 || *s2)
	{
		if (*s1 != *s2)
			return ((*(unsigned char *)s1) - (*(unsigned char *)s2));
		s1++;
		s2++;
	}
	return (0);
}

int	ft_unset(char **argv, t_envp **envp)
{
	t_envp	*prev;
	t_envp	*curr;
	
	if (!argv[1])
		return ;
	curr = *envp;
	while (curr && ft_strcmp(argv[1], curr->key) != 0)
	{
		prev = curr;
		curr = curr->next;
	}
	if (ft_sdtrcmp(argv[1], curr->key) == 0)
	{
		if (curr == *envp)
			*envp = (*envp)->next;
		else
			prev->next = curr->next;
		deallocate(curr);
	}
	return (0);
}