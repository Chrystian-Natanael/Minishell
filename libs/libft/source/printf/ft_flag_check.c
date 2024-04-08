/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 09:18:07 by cnatanae          #+#    #+#             */
/*   Updated: 2023/12/04 09:25:50 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	ft_flag_check(const char *format, va_list ap)
{
	int	count;

	count = 0;
	if (*format == '#')
		count += ft_hash(++format, ap);
	else if (*format == '+')
		count += ft_plus(++format, ap);
	else if (*format == ' ')
		count += ft_space(++format, ap);
	return (count);
}
