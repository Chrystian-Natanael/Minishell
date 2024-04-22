/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deallocate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:38:08 by cnatanae          #+#    #+#             */
/*   Updated: 2024/04/22 12:04:15 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

static void	helper(t_typetree *typetree, void *address);
static void	*find_min_address(t_typetree *typetree);

void	deallocate(void *address)
{
	typetree_delete(address);
}

void	typetree_delete(void *address)
{
	t_typetree	*typetree;

	typetree = typetree_get();
	helper(typetree, address);
}

static void	*find_min_address(t_typetree *typetree)
{
	t_typetree	min_root;
	void		*min_address;

	if ((*typetree)->ltree == NULL)
	{
		min_root = *typetree;
		min_address = min_root->address;
		*typetree = min_root->rtree;
		free(min_root);
	}
	else
		min_address = find_min_address(&((*typetree)->ltree));
	return (min_address);
}

static void	helper(t_typetree *typetree, void *address)
{
	t_typetree	old_root;

	if (*typetree == NULL)
		return ;
	else if ((*typetree)->address == address)
	{
		if ((*typetree)->rtree != NULL)
		{
			(*typetree)->address = find_min_address(&((*typetree)->rtree));
			free(address);
		}
		else
		{
			old_root = *typetree;
			*typetree = (*typetree)->ltree;
			free(old_root->address);
			free(old_root);
		}
	}
	else if (address < (*typetree)->address)
		helper(&((*typetree)->ltree), address);
	else if (address > (*typetree)->address)
		helper(&((*typetree)->rtree), address);
	typetree_rebalance(typetree);
}
