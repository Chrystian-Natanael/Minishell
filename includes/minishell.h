/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 08:25:10 by cnatanae          #+#    #+#             */
/*   Updated: 2024/05/01 09:27:55 by cnatanae         ###   ########.fr       */
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
	REDIR_INPUT,
	REDIR_OUTPUT,
	L_PAREN,
	R_PAREN,
	EXPRESSION,
	COMMAND,
	DOLLAR,
	OR,
	AND,
	HEREDOC,
	OUTPUT_APPEND
};

typedef struct s_token
{
	enum e_token	type;
	char			*lexema;
	struct s_token	*next;
}	t_token;

typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}	t_envp;

char	*envp_get(char *key, t_envp *envp);
void	envp_insert(char *key, char *value, t_envp **envp);
t_envp	*create_envp(char **envp);
void	free_split(char **array);
char	*get_username(t_envp *envp);

//--------------------------------------- Lexical Analysis

t_token	*lexer(char *line);

void	lst_addnew(t_token **list, enum e_token type, char *lexema);
void	print_tokens(t_token *token); // ! Apagar

#endif