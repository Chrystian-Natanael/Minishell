/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 08:25:10 by cnatanae          #+#    #+#             */
/*   Updated: 2024/05/31 12:30:28 by krocha-h         ###   ########.fr       */
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

/*For use linux limits' macros*/
# include "linux/limits.h"

/*For use garbage_collector functions*/
# include "garbage_collector.h"

/*For use readline functions*/
# include <readline/history.h>
# include <readline/readline.h>

/*For use system functions */
# include <stdio.h>

/**/
# include <sys/wait.h>

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
	CMD,
	FILE_NAME,
	SUB_SHELL,
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

typedef struct s_bin
{
	char			*cmd;
	// t_token			*args;  ---- lista de argumentos
	enum e_token	type;
	struct s_bin	*left;
	struct s_bin	*right;
}					t_bin;

char	*envp_get(char *key, t_envp *envp);
void	envp_insert(char *key, char *value, t_envp **envp);
t_envp	*create_envp(char **envp);
void	free_split(char **array);
char	*get_username(t_envp *envp);

//--------------------------------------- Lexical Analysis

t_token	*lexer(char *line);

//--------------------------------------- Utils

void	lst_addnew(t_token **list, enum e_token type, char *lexema);
void	print_tokens(t_token *token); // ! Apagar
void	print_tree(t_bin *bin, int level); // ! Apagar
int		is_metacharacter(char a, char b);
int		get_token_type(char *line, int i);

//--------------------------------------- Expression Analysis
t_token	*cmd_parsing(t_token *token);
void	lst_contatenate(t_token **list, char *lexema);
void	lst_contatenate_redir(t_token **list, char *lexema);
void	lstadd_back(t_token **lst, t_token *new);
void	cmd_parsing_aux(t_token **head, t_token **cmds, t_token **tmp);
char	*return_lexema(t_token *token);

//--------------------------------------- Syntax Analysis
int		syntax_error(t_token *token);

//--------------------------------------- Executor + binarytree

void	execute(t_token *tokens, char **envp_origin);
int		precedence(enum e_token type);
t_bin	*new_node(char *cmd, enum e_token type);
t_bin	*create_tree(t_token *tokens);
t_token	*return_token_list(t_token *tokens, t_token *max_prec);

int		exec_cmd(t_bin *bin, char **envp_origin);
char	*get_path_cmd(char *cmd, char **envp_origin);
int		exec_tree(t_bin *bin, char **envp_origin);

//--------------------------------------- Builtin
int		pwd(void);

#endif
