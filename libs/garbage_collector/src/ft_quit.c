/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:05:04 by cnatanae          #+#    #+#             */
/*   Updated: 2024/04/22 11:53:25 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

static void	helper(t_typetree typetree);

void	quit(int code)
{
	typetree_destroy();
	exit(code);
}

static void	helper(t_typetree typetree)
{
	if (typetree == NULL)
		return ;
	helper(typetree->ltree);
	helper(typetree->rtree);
	if (typetree->address)
	{
		free(typetree->address);
		typetree->address = NULL;
	}
	if (typetree)
	{
		free(typetree);
		typetree = NULL;
	}
}

void	typetree_destroy(void)
{
	t_typetree	*typetree;

	typetree = typetree_get();
	helper(*typetree);
}