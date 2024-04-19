/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:22:18 by cnatanae          #+#    #+#             */
/*   Updated: 2024/04/19 18:35:40 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTOR_H
#define GARBAGE_COLLECTOR_H

#include "libft.h"

typedef struct s_typetree	*t_typetree;

struct s_typetree {
	t_typetree		ltree;
	t_typetree		rtree;
	void			*address;
	int				height;
};


void		*allocate(unsigned int size);
t_typetree	typetree_create(void *address);
int			typetree_get_height(t_typetree typetree);
void		typetree_update_height(t_typetree typetree);
void		typetree_insert(void *address);
void		typetree_rebalance(t_typetree *typetree);
t_typetree	*typetree_get(void);

#endif