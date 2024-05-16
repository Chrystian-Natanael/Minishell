/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:44:27 by cnatanae          #+#    #+#             */
/*   Updated: 2024/05/16 17:28:06 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file executor.c
 * @brief This file contains the executor functions
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/05/06
*/

#include "minishell.h"


void	execute(t_token *tokens, t_envp *envp)
{
	t_bin	*bin;

	bin = create_binary(tokens, envp);
}

t_bin	*create_binary(t_token *tokens, t_envp *envp)
{
	t_bin	*bin;

	bin = (t_bin *)allocate(sizeof(t_bin));
	if (bin == NULL)
	{
		ft_printf("\033[91mError: \033[0mMalloc failed\n");
		quit(1);
	}
	create_root(&bin, tokens);
	create_tree(tokens, bin, envp);
	return (bin);
}

void	create_root(t_bin **bin, t_token *tokens)
{
	t_token	*address;
	t_token	*tmp;

	tmp = tokens;
	address = NULL;
	while (tmp)
	{
		if (tmp->type == AND || tmp->type == OR)
			address = tmp;
		tmp = tmp->next;
	}
}