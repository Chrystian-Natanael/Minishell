/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 16:11:57 by krocha-h          #+#    #+#             */
/*   Updated: 2024/06/21 17:36:44 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file aux_utils.c
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

char	*ft_strndup(const char *s, int n)
{
	char	*dup;
	int		idx;

	dup = ft_calloc(n + 1, sizeof(char));
	if (!dup)
		return (NULL);
	idx = 0;
	while (*s && idx < n)
		dup[idx++] = *(s++);
	return (dup);
}

int	ternary(int condition, int if_true, int if_false)
{
	if (condition)
		return (if_true);
	return (if_false);
}

void	line_feed(int sig)
{
	g_sign = sig;
	ft_putstr_fd("\n", 1);
}
