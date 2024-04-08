/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 09:03:10 by cnatanae          #+#    #+#             */
/*   Updated: 2023/10/18 11:52:47 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t count)
{
	if (!(dest || src))
		return (NULL);
	if ((char *)dest < (char *)src)
		return (ft_memcpy(dest, src, count));
	while (count--)
	((char *)dest)[count] = ((char *)src)[count];
	return (dest);
}
