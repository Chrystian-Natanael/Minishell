/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_build.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:17:28 by cnatanae          #+#    #+#             */
/*   Updated: 2023/12/06 12:38:43 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"
#include "../include/libft.h"

int	ft_print_build(const char *format, va_list ap)
{
	int	count;

	count = 0;
	while (*format)
	{
		if (*format == '%')
		{
			if ((ft_strrchr(FLAGS, *(format + 1))))
			{
				count += ft_flag_check(++format, ap);
				while ((ft_strrchr(FLAGS, *(format))) || ft_isdigit(*format))
					format++;
			}
			else
				count += ft_parse(*(++format), ap);
		}
		else
			count += ft_putchar_fd(*format, ON);
		format++;
	}
	va_end(ap);
	return (count);
}
