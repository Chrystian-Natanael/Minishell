/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 17:06:11 by krocha-h          #+#    #+#             */
/*   Updated: 2024/06/09 17:08:28 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file utils_2.c
 * @brief This file contains the pwd function
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/06/01
*/

#include "minishell.h"

char	*ft_strndup(const char *s, int n)
{
	char	*dup;
	int		idx;

	dup = ft_calloc(n, sizeof(char));
	if (!dup)
		return (NULL);
	idx = 0;
	while (*s && idx < n)
		dup[idx++] = *(s++);
	return (dup);
}