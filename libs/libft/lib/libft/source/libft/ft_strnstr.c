/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:53:07 by cnatanae          #+#    #+#             */
/*   Updated: 2023/10/13 14:50:41 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	idx_a;
	size_t	idx_b;

	if (*little == '\0')
	{
		return ((char *)big);
	}
	idx_a = 0;
	while (big[idx_a] && idx_a < len)
	{
		idx_b = 0;
		while ((big[idx_a + idx_b] == little[idx_b]) && (idx_a + idx_b) < len)
		{
			idx_b++;
			if (little[idx_b] == '\0')
			{
				return ((char *)&big[idx_a]);
			}
		}
		idx_a++;
	}
	return (NULL);
}
