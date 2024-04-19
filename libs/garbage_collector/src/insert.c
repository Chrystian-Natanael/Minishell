/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:17:42 by cnatanae          #+#    #+#             */
/*   Updated: 2024/04/19 18:28:16 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

static void	helper(t_typetree *typetree, void *address)
{
	if (*typetree == NULL)
		*typetree = typetree_create(address);
	else if (address == (*typetree)->address)
		return ;
	else
	{
		if (address < (*typetree)->address)
			helper(&(*typetree)->ltree, address);
		else
			helper(&(*typetree)->rtree, address);
		typetree_rebalance(typetree);
	}
}

void	typetree_insert(void *address)
{
	t_typetree *typetree;

	typetree = typetree_get();
	helper(typetree, address);
}
