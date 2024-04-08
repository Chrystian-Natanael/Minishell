/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plus.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 09:19:59 by cnatanae          #+#    #+#             */
/*   Updated: 2023/12/06 12:38:10 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"
#include "../include/libft.h"

int	ft_plus(const char *format, va_list ap)
{
	long long int	value;

	while (*format == '+')
		format++;
	if (*format == 'd' || *format == 'i')
	{
		value = (t_lolo)va_arg(ap, int);
		if (value >= 0)
			return (ft_putchar_fd('+', 1) + ft_putnbr_hex
				(value, BASE_DEC));
		return (ft_putnbr_hex(value, BASE_DEC));
	}
	return (0);
}
