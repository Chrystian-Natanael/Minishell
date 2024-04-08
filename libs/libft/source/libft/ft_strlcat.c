/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:53:10 by cnatanae          #+#    #+#             */
/*   Updated: 2023/10/19 06:09:31 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_dst;
	size_t	len_max;
	size_t	len_src;

	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	len_max = len_dst + len_src;
	if (size == 0 || len_dst >= size)
		return (len_src + size);
	else
	{
		while (len_dst < (size - 1) && *src)
		{
			dst[len_dst] = *src++;
			len_dst++;
		}
		dst[len_dst] = '\0';
	}
	return (len_max);
}
