/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 20:50:43 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/21 22:04:27 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file lst_utils.c
 * @brief This file contains the lst functions
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/06/21
*/

#include "minishell.h"

void	lst_contatenate(t_token **list, char *lexeme)
{
	t_token	*new;

	new = (t_token *)allocate(sizeof(t_token));
	new->type = CMD;
	new->lexeme = lexeme;
	new->next = NULL;
	if (*list == NULL)
		*list = new;
	else
	{
		(*list)->lexeme = ft_strjoin((*list)->lexeme, " ");
		typetree_insert((*list)->lexeme);
		(*list)->lexeme = ft_strjoin((*list)->lexeme, lexeme);
		typetree_insert((*list)->lexeme);
	}
}

void	lst_contatenate_redir(t_token **list, char *lexeme)
{
	t_token	*new;

	new = (t_token *)allocate(sizeof(t_token));
	new->type = FILE_NAME;
	new->lexeme = lexeme;
	new->next = NULL;
	if (*list == NULL)
		*list = new;
	else
	{
		(*list)->lexeme = ft_strjoin((*list)->lexeme, lexeme);
		typetree_insert((*list)->lexeme);
	}
}

void	init_organize(t_organize *organize, t_token **token)
{
	organize->tmp = *token;
	organize->idx = 0;
	organize->redir = NULL;
	organize->point = 0;
}

void	init_parsing(t_parsing *parsing, t_token **token)
{
	parsing->i = 0;
	parsing->tmp = *token;
	parsing->cmds = NULL;
	parsing->head = NULL;
}
