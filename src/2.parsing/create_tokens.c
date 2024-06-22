/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 20:52:55 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/21 21:13:01 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file create_tokens.c
 * @brief This file contains the create_tokens functions
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/06/21
*/

#include "minishell.h"

int	is_sub_shell(t_parsing *parsing)
{
	parsing->i++;
	while (parsing->tmp && (parsing->tmp->type != R_PAREN
			|| parsing->i != 0))
	{
		lst_contatenate(&parsing->cmds, return_lexeme(parsing->tmp));
		parsing->tmp = parsing->tmp->next;
		if (parsing->tmp && parsing->tmp->type == R_PAREN)
			parsing->i--;
		else if (parsing->tmp && parsing->tmp->type == L_PAREN)
			parsing->i++;
	}
	if (parsing->tmp && parsing->tmp->type == R_PAREN)
		lst_contatenate(&parsing->cmds, return_lexeme(parsing->tmp));
	if (!parsing->tmp && parsing->i != 0)
		return (0);
	parsing->tmp = parsing->tmp->next;
	parsing->cmds->type = SUB_SHELL;
	return (1);
}

void	is_cmd(t_parsing *parsing)
{
	while (parsing->tmp && parsing->tmp->type != PIPE
		&& parsing->tmp->type != OR
		&& parsing->tmp->type != AND && parsing->tmp->type != L_PAREN
		&& parsing->tmp->type != R_PAREN && !is_redirect(parsing->tmp->type))
	{
		if ((parsing->tmp->lexeme && *parsing->tmp->lexeme != '\0')
			|| parsing->tmp->type != WORD)
			lst_contatenate(&parsing->cmds, return_lexeme(parsing->tmp));
		parsing->tmp = parsing->tmp->next;
	}
}
