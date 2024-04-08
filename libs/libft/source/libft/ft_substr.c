/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:43:39 by cnatanae          #+#    #+#             */
/*   Updated: 2023/10/19 07:00:57 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			idx_a;
	size_t			idx_b;
	unsigned int	strlen;
	char			*substr;

	idx_a = start;
	idx_b = 0;
	strlen = ft_strlen(s);
	if (start >= strlen)
		return (ft_strdup(""));
	if (start + len > strlen)
		len = strlen - start;
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	while (idx_b < len)
		substr[idx_b++] = s[idx_a++];
	substr[idx_b] = '\0';
	return (substr);
}
