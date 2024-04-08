/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dolstadd_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:52:01 by cnatanae          #+#    #+#             */
/*   Updated: 2024/03/12 08:32:50 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dolstadd_back(t_dolist **lst, t_element *new)
{
	t_element	*aux;

	aux = (*lst)->first;
	if (aux == NULL)
	{
		(*lst)->first = new;
		return ;
	}
	while (aux->next)
		aux = aux->next;
	aux->next = new;
	new->prev = aux;
	(*lst)->size++;
	(*lst)->last = new;
}
