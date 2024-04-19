/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:16:38 by cnatanae          #+#    #+#             */
/*   Updated: 2024/04/19 18:33:16 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

t_typetree	typetree_create(void *address)
{
	t_typetree	typetree;

	typetree = malloc(sizeof(struct s_typetree));
	if (typetree == NULL)
	{
		// Destruir a arvore binária
		return (NULL);
	}
	typetree->address = address;
	typetree->ltree = NULL;
	typetree->rtree = NULL;
	typetree->height = 1;
	return (typetree);
}
