/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 20:43:44 by krocha-h          #+#    #+#             */
/*   Updated: 2024/06/21 20:49:26 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file is_utils.c
 * @brief This file contains the utils functions
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/06/19
*/

#include "minishell.h"

int	is_redirect(int type)
{
	return (type == REDIR_INPUT || type == REDIR_OUTPUT
		|| type == OUTPUT_APPEND || type == HEREDOC);
}

int	is_redirect_input(int type)
{
	return (type == REDIR_INPUT || type == HEREDOC);
}

int	is_parentheses(int type)
{
	return (type == L_PAREN || type == R_PAREN);
}

int	is_and_or(int type)
{
	return (type == AND || type == OR);
}
