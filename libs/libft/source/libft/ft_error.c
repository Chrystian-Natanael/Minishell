/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 10:27:06 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/03 09:12:05 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_error(char *name, char *str1, char *str2, int ret_code)
{
	ft_putstr_fd(name, ERROR);
	ft_putstr_fd(str1, ERROR);
	ft_putendl_fd(str2, ERROR);
	return (ret_code);
}
