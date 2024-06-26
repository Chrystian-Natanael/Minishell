/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 08:29:20 by cnatanae          #+#    #+#             */
/*   Updated: 2024/05/01 11:15:17 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*last_case;

	c = c % 256;
	last_case = NULL;
	while (s && *s)
	{
		if (*s == c)
			last_case = s;
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return ((char *)last_case);
}
