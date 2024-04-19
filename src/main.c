/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 08:19:03 by cnatanae          #+#    #+#             */
/*   Updated: 2024/04/19 18:30:54 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*str;
	char	*str2;
	int		idx;
	str = (char *)allocate(sizeof(char) * 10);
	str2 = (char *)allocate(sizeof(char) * 10);
	if (str)
	{
		idx = 0;
		while(idx < 10)
		{
			str[idx] = 'a';
			idx++;
		}
	}
	if (str2)
	{
		idx = 0;
		while(idx < 10)
		{
			str2[idx] = 'b';
			idx++;
		}
	}
	ft_printf("%s\n", str);
	ft_printf("%s\n", str2);
	return (0);
}