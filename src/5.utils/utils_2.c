/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 16:11:57 by krocha-h          #+#    #+#             */
/*   Updated: 2024/06/09 17:06:26 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file utils_2.c
 * @brief This file contains the pwd function
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/06/01
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

int	ft_isonlynum(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && ft_isdigit(str[i]))
		i++;
	if (!str || str[i] == '\0')
		return (1);
	return (0);
}

int	find_key_size(char *str)
{
	int	size;

	size = 0;
	while (str[size] && str[size] != '=')
		size++;
	return (size);
}
void	change_status(t_envp **envp, int status)
{
	char	*status_str;
	t_envp	*curr;

	curr = *envp;
	while (curr)
	{
		if (ft_strcmp(curr->key, "?") == 0)
		{
			status_str = ft_itoa(status);
			typetree_insert(status_str);
			curr->value = status_str;
			return ;
		}
		curr = curr->next;
	}
}

int	ternary(int condition, int if_true, int if_false)
{
	if (condition)
		return (if_true);
	return (if_false);
}

void	ending(int status)
{
	rl_clear_history();
	close(0);
	close(1);
	close(2);
	quit(status);
}
