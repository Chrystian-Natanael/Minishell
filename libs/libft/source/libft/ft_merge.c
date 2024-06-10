/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_merge.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:15:00 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/07 14:33:19 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_strmerge.c
 * @brief Implementation of the ft_strmerge function.
 */

#include "libft.h"

/**
 * @brief Merges two strings into one. The two strings are freed.
 * @param s1 The first string.
 * @param s2 The second string.
 * @return The merged string.
 */
char	*ft_strmerge(char *s1, char *s2)
{
	char	*merged;

	merged = ft_strjoin(s1, s2);
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (merged);
}