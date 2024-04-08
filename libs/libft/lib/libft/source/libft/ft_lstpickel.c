/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpickel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 13:41:11 by cnatanae          #+#    #+#             */
/*   Updated: 2024/03/09 14:02:52 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_element	*ft_lstpickel(t_dolist *lst, int index)
{
	t_element	*el;

	if ((!lst) || (index < 0 && - index > (int)lst->size)
		|| (index >= 0 && index + 1 > (int)lst->size))
		return (NULL);
	if (index < 0)
	{
		el = lst->last;
		while (++index)
			el = el->prev;
	}
	else
	{
		el = lst->first;
		while (index--)
			el = el->next;
	}
	return (el);
}
