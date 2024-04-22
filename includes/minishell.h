/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 08:25:10 by cnatanae          #+#    #+#             */
/*   Updated: 2024/04/22 17:32:47 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/**
 * @file minishell.h
 * @brief This file contains the minishell functions and structures
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/04/08
*/

/*For use libft functions*/
# include "libft.h"

/*For use garbage_collector functions*/
# include "garbage_collector.h"

/*For use readline functions*/
# include <readline/history.h>
# include <readline/readline.h>

/*For use system functions */
# include <stdio.h>

/**
 * @brief Enum e_token
 * @details enum e_token is a enum that stores the token types
*/
enum e_token
{
	WORD,
	PIPE,
	REDIRECT_INPUT,
	REDIRECT_HEREDOC,
	REDIRECT_OUTPUT,
	REDIRECT_OUTPUT_APPEND,
	OR,
	AND,
	L_PAREN,
	R_PAREN,
	EXPRESSION,
	COMMAND,
	DOLLAR
};

#endif