/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 12:20:52 by cnatanae          #+#    #+#             */
/*   Updated: 2023/12/06 13:00:10 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_putnbr_hex(long long num, char *base)
{
	int			count;
	int			len_base;

	len_base = ft_strlen(base);
	count = 0;
	if (num < 0)
	{
		count += ft_putchar_fd('-', 1);
		num = -num;
	}
	if (num >= len_base)
		count += ft_putnbr_hex(num / len_base, base);
	count += ft_putchar_fd(base[num % len_base], 1);
	return (count);
}
