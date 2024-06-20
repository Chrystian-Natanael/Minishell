/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 08:25:10 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/20 16:26:02 by krocha-h         ###   ########.fr       */
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
# define MAX_NB "9223372036854775807"
# define MIN_NB "-9223372036854775808"

# include <termios.h>

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

# include <signal.h>

extern int	g_sign;

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
	OR,
	AND,
	HEREDOC,
	OUTPUT_APPEND
};

typedef struct s_token
{
	enum e_token	type;
	char			*lexeme;
	struct s_token	*next;
}	t_token;

typedef struct s_aux_redirect
{
	t_token	*redir;
	t_token	*file_name;
}	t_aux_redirect;

typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}	t_envp;

typedef struct s_bin
{
	char			*cmd;
	int				fd;
	enum e_token	type;
	struct s_bin	*left;
	struct s_bin	*right;
}	t_bin;

typedef struct s_data
{
	int		status;
	int		count_files;
	char	*line;
	char	*read_line;
	t_envp	*my_envp;
	t_token	*token;
	t_token	*expr;
}	t_data;

//--------------------------------------- Menu
void	clearscreen(void);
void	settextcolor(int color);
void	loadingbar(void);

//--------------------------------------- Init
void	ending(int status, t_data *data);
int		verify_line(char **line);
char	*get_readline(t_envp *envp, t_data *data);

//--------------------------------------- Signal
void	init_signals(void);
void	define_signals_exec(int pid);
void	heredoc_signals(void);
void	line_feed(int sig);

//--------------------------------------- Envp
t_envp	*create_envp(char **envp);
char	*envp_get(char *key, t_envp *envp);
int		count_envp(char **envp);
int		size_envp(t_envp **envp);
void	envp_insert(char *key, char *value, t_envp **envp);

//--------------------------------------- Lexical Analysis
t_token	*lexer(char *line);
int		get_token_type(char *line, int i);
char	*return_lexeme(t_token *token);
int		quote_is_closed(char *line, int *i);
int		close_quote(char *line, int **i);

//--------------------------------------- Expression Analysis
t_token	*cmd_parsing(t_token *token, t_envp **envp);
void	lst_contatenate(t_token **list, char *lexeme);
void	lst_contatenate_redir(t_token **list, char *lexeme);
void	lstadd_back(t_token **lst, t_token *new);
void	cmd_parsing_aux(t_token **head, t_token **cmds, t_token **tmp);
char	*return_lexeme(t_token *token);

//--------------------------------------- Syntax Analysis
int		syntax_error(t_token *token);
int		syntax_expr(t_token *expr);

//--------------------------------------- Executor + binarytree
t_bin	*new_node(char *cmd, enum e_token type);
t_bin	*create_tree(t_token *tokens);
t_token	*return_token_list(t_token *tokens, t_token *max_prec);
void	create_left_right(t_token *max_prec, t_token **list, \
t_token **tokens, t_bin **bin);
int		execute(t_token *tokens, t_data *data);
int		precedence(enum e_token type);
char	*get_path_cmd(t_envp **envp, char *cmd);
void	exec_init(char ***cmd, int *exit_status, t_bin *bin, t_data **data);
int		exec_cmd(t_bin *bin, t_data **data);
int		exec_tree(t_bin *bin, t_data **data);
char	**create_envp_array(t_envp **envp);
int		exec_and(t_bin *bin, t_data **data);
int		exec_or(t_bin *bin, t_data **data);
int		exec_pipe(t_bin *bin, t_data **data);
int		exec_sub_shell(t_bin *bin, t_data **data);

//--------------------------------------- Builtin
int		check_exec_builtin(char **cmd, t_envp **envp, t_data *data);
int		ft_echo(char **argv);
int		ft_env(char **argv, t_envp **envp);
int		ft_exit(char **argv, t_data *data);
int		ft_export(char **argv, t_envp **envp);
int		ft_pwd(void);
int		ft_unset(char **argv, t_envp **envp);
int		ft_cd(char **argv, t_envp **envp);
char	**sort_envp(t_envp **envp);

//--------------------------------------- Expander
void	expander(int *idx, char **cmd, t_envp *envp, char **dst);
void	expander_validation(t_data **data, char **cmd);
char	*expan_get(t_token *token, t_envp *envp);

//--------------------------------------- Heredoc
int		exec_heredoc(t_token **token, int *count_files);
void	heredoc_validation(t_token **tokens, int *count_files);

//--------------------------------------- Redirect
void	organize_redirects(t_token **token);
int		is_redirect(int type);
int		count_redirects(t_token *token);
int		exec_redirect(t_bin *bin, t_data **data);

//--------------------------------------- Utils
void	lst_addnew(t_token **list, enum e_token type, char *lexeme);
int		is_metacharacter(char a, char b);
int		args_count(char **argv);
int		ft_strcmp(char *s1, char *s2);
int		ft_isonlynum(char *str);
void	free_split(char **array);
int		find_key_size(char *str);
char	*ft_strndup(const char *s, int n);
int		ternary(int condition, int if_true, int if_false);
int		is_valid_var(char letter);
void	add_char(char **line, char c);
void	change_status(t_envp **envp, int status);
void	value_concat(char **split);
char	*create_path(t_envp *envp, char *cmd);
int		quote_error(t_token *tokens);

#endif
