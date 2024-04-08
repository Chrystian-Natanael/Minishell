/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_after.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:12:33 by cnatanae          #+#    #+#             */
/*   Updated: 2024/03/09 14:12:44 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_after(t_dolist *lst, t_element *ref, t_element *el)
{
	if (!el)
		return ;
	if (lst->last == ref)
		lst->last = el;
	el->next = ref->next;
	if (el->next)
		el->next->prev = el;
	ref->next = el;
	el->prev = ref;
	lst->size++;
}
