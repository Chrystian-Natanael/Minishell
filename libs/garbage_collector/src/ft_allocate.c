/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_allocate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:28:04 by cnatanae          #+#    #+#             */
/*   Updated: 2024/04/19 18:31:37 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

void	*allocate(unsigned int size)
{
	void			*address;
	unsigned int	idx;

	address = malloc(size);

	if (address == NULL)
	{
		// deletar a arvore binária
		exit (1);
	}
	idx = 0;
	while (idx < size)
	{
		((unsigned char *)address)[idx] = 0;
		idx++;
	}
	typetree_insert(address);
	return (address);
}
