/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 12:13:51 by cnatanae          #+#    #+#             */
/*   Updated: 2024/03/09 12:17:10 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	ft_isspace_atol(const char *nptr)
{
	int	idx;

	idx = 0;
	while ((nptr[idx] == '\f') || (nptr[idx] == '\n')
		|| (nptr[idx] == '\r') || (nptr[idx] == '\t')
		|| (nptr[idx] == '\v') || (nptr[idx] == ' '))
	{
		idx++;
	}
	return (idx);
}

static int	ft_odd_atol(char c)
{
	int	odd;

	odd = 1;
	if (c == '-')
		odd = -1;
	return (odd);
}

long	ft_atol(const char *nptr)
{
	int		odd;
	long	value;
	long	idx;

	value = 0;
	idx = ft_isspace_atol(nptr);
	odd = ft_odd_atol(nptr[idx]);
	while (nptr[idx] == '+' || nptr[idx] == '-')
		idx++;
	while (nptr[idx] >= '0' && nptr[idx] <= '9')
		value = value * 10 + (nptr[idx++] - '0');
	return (value * odd);
}
