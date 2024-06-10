/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 08:25:10 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/10 10:50:10 by cnatanae         ###   ########.fr       */
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

# define TRUN 0x00000242

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
	// DOLLAR,
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
	enum e_token	type;
	struct s_bin	*left;
	struct s_bin	*right;
}	t_bin;

//----------- DISTRIBUTE OR REORGANIZE ###

char	*envp_get(char *key, t_envp *envp);
int		count_envp(char **envp);
int		size_envp(t_envp **envp);
void	value_concat(char **split);
void	envp_insert(char *key, char *value, t_envp **envp);
t_envp	*create_envp(char **envp);
char	*get_username(t_envp *envp);

//--------------------------------------- Lexical Analysis

t_token	*lexer(char *line);

//--------------------------------------- Utils

void	lst_addnew(t_token **list, enum e_token type, char *lexema);
void	print_tokens(t_token *token); // ! Apagar
void	print_tree(t_bin *bin, int level); // ! Apagar
int		is_metacharacter(char a, char b);
int		get_token_type(char *line, int i);
int		args_count(char **argv);
int		ft_strcmp(char *s1, char *s2);
int		ft_isonlynum(char *str);
void	free_split(char **array);
int		find_key_size(char *str);
char	*ft_strndup(const char *s, int n);

//--------------------------------------- Expression Analysis

t_token	*cmd_parsing(t_token *token, t_envp **envp);
void	lst_contatenate(t_token **list, char *lexema);
void	lst_contatenate_redir(t_token **list, char *lexema);
void	lstadd_back(t_token **lst, t_token *new);
void	cmd_parsing_aux(t_token **head, t_token **cmds, t_token **tmp);
char	*return_lexema(t_token *token);

//--------------------------------------- Syntax Analysis

int		syntax_error(t_token *token);
int		syntax_expr(t_token *expr);

//--------------------------------------- Executor + binarytree

int		execute(t_token *tokens, t_envp **envp);
int		precedence(enum e_token type);
t_bin	*new_node(char *cmd, enum e_token type);
t_bin	*create_tree(t_token *tokens);
t_token	*return_token_list(t_token *tokens, t_token *max_prec);
char	*get_path_cmd(t_envp **envp, char *cmd);
int		exec_cmd(t_bin *bin, t_envp **envp);
int		exec_tree(t_bin *bin, t_envp **envp);
char	**t_envp_to_char(t_envp **envp);
int		exec_and(t_bin *bin, t_envp **envp);
int		exec_or(t_bin *bin, t_envp **envp);
int		exec_pipe(t_bin *bin, t_envp **envp);
int		exec_sub_shell(t_bin *bin, t_envp **envp);

//--------------------------------------- Builtin

int		check_exec_builtin(char **cmd, t_envp **envp);
int		ft_echo(char **argv);
int		ft_env(char **argv, t_envp **envp);
int		ft_exit(char **argv);
int		ft_export(char **argv, t_envp **envp);
int		ft_pwd(void);
int		ft_unset(char **argv, t_envp **envp);
int		ft_cd(char **argv, t_envp **envp);

//----------- DISTRIBUTE OR REORGANIZE ###

void	change_status(t_envp **envp, int status);
char	*expan_get(t_token *token, t_envp *envp);

//----------- DISTRIBUTE OR REORGANIZE ###

void	expander(int	*idx, t_token	**token, t_envp	*envp, char	**dst);
void	expander_validation(t_token **tokens, t_envp **envp);
int		is_valid_var(char letter);
int		ternary(int condition, int if_true, int if_false);
void	add_char(char **line, char c);

//----------- DISTRIBUTE OR REORGANIZE ###

int		exec_redir_out(t_bin *bin, t_envp **envp);
int		exec_redir_output(t_bin *bin, t_envp **envp);
int		exec_redir_append(t_bin *bin, t_envp **envp);

int		exec_redir_input(t_bin *bin, t_envp **envp);


//----------- HEREDOC ###

int		exec_heredoc(t_token **token);
void	heredoc_validation(t_token **tokens);

void	ending(int status);

#endif
