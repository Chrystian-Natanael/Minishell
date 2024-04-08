/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 08:06:19 by cnatanae          #+#    #+#             */
/*   Updated: 2023/10/23 19:20:23 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size(long int n)
{
	if (n < 0)
		return (1 + ft_size(-n));
	if ((n / 10) == 0)
		return (1);
	else
		return (1 + ft_size(n / 10));
}

static void	ft_convert(long int n, char *value, long int size)
{
	if (n < 0)
	{
		value[0] = '-';
		n *= -1;
	}
	if (n >= 10)
		ft_convert((n / 10), value, (size - 1));
	value[size] = (n % 10) + '0';
}

char	*ft_itoa(int n)
{
	char		*value;
	long int	size;

	size = ft_size(n);
	value = (char *)ft_calloc((size + 1), sizeof(char));
	if (!value)
		return (NULL);
	value[size--] = '\0';
	ft_convert(n, value, size);
	return (value);
}
