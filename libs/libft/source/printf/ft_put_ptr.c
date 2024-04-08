/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_ptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 09:21:20 by cnatanae          #+#    #+#             */
/*   Updated: 2023/12/06 12:39:05 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"
#include "../include/libft.h"

int	ft_put_ptr(unsigned long long pointer, int prefix)
{
	int			count;

	count = 0;
	if (!pointer)
	{
		count += ft_putstr_fd(NULL_PTR, ON);
		return (count);
	}
	if (prefix)
		count += ft_putstr_fd("0x", ON);
	if (pointer >= BASE_HEXA)
		count += ft_put_ptr(pointer / BASE_HEXA, OFF);
	count += ft_putchar_fd(HEXAMIN[pointer % BASE_HEXA], ON);
	return (count);
}
