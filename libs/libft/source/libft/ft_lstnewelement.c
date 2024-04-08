/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnewelement.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:09:05 by cnatanae          #+#    #+#             */
/*   Updated: 2024/03/09 18:14:50 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_element	*ft_lstnewelement(void *content)
{
	t_element	*el;

	el = ft_calloc(1, sizeof(t_element));
	if (el == NULL)
		return (NULL);
	el->content = content;
	return (el);
}
