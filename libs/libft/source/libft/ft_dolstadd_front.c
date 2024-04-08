/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dolstadd_front.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:44:39 by cnatanae          #+#    #+#             */
/*   Updated: 2024/03/12 08:30:05 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dolstadd_front(t_dolist **lst, t_element *new)
{
	if (!lst || !new)
		return ;
	new->next = (*lst)->first;
	new->prev = NULL;
	(*lst)->first->prev = new;
	(*lst)->first = new;
	(*lst)->size++;
}
