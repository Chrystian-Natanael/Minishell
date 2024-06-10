/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 19:50:30 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/10 12:32:48 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file utils_1.c
 * @brief This file contains the utils functions
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/04/27
*/

#include "minishell.h"

char	*get_readline(t_envp *envp)
{
	char	*readline;
	char	*final_string;
	char	*pwd;
	char	*str1;
	char	*str2;
	char	cwd[PATH_MAX];

	pwd = NULL;
	readline = envp_get("USER", envp);
	if (getcwd(cwd, PATH_MAX))
		pwd = ft_strdup(cwd);
	if (!readline)
		readline = "minishell";
	str2 = ft_strrchr(pwd, '/');
	if (!str2)
		str2 = "//";
	str1 = ft_strjoin(++str2, " $\033[0m ");
	str2 = ft_strjoin("\033[92m", readline);
	typetree_insert(str2);
	typetree_insert(pwd);
	str2 = ft_strjoin(str2, "\033[0m:\033[34m");
	final_string = ft_strjoin(str2, str1);
	typetree_insert(final_string);
	typetree_insert(str2);
	typetree_insert(str1);
	return (final_string);
}

void	lst_addnew(t_token **list, enum e_token type, char *lexema)
{
	t_token	*new;
	t_token	*tmp;

	tmp = *list;
	new = allocate(sizeof(t_token));
	new->type = type;
	new->lexema = lexema;
	new->next = NULL;
	if (*list == NULL)
		*list = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	free_split(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	is_metacharacter(char a, char b)
{
	if (a == '|' || a == '(' || a == ')' || a == '<' || a == '>')
		return (1);
	else if (a == '&' && b == '&')
		return (1);
	return (0);
}

int	args_count(char **argv)
{
	int	count;

	count = 0;
	while (argv[count])
		count++;
	return (count);
}

// --------------------------------- APAGAR A PARTIR DAQUI -------------------------------------//

void	print_tree(t_bin *bin, int level)
{
	if (bin == NULL)
		return ;
	
	if (bin)
	{
		print_tree(bin->right, level + 1);
		ft_printf("\n\n");
		for (int i = 0; i < level; i++)
			ft_printf("\t");
		ft_printf("\033[91m|\033[0m %s \033[91m|\033[0m\n", bin->cmd);
		print_tree(bin->left, level + 1);
	}
}

void	print_tokens(t_token *token)
{
	t_token	*tmp;
	char	*type;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == WORD)
			type = "WORD";
		else if (tmp->type == PIPE)
			type = "PIPE";
		else if (tmp->type == REDIR_INPUT)
			type = "REDIR_INPUT";
		else if (tmp->type == REDIR_OUTPUT)
			type = "REDIR_OUTPUT";
		else if (tmp->type == L_PAREN)
			type = "L_PAREN";
		else if (tmp->type == R_PAREN)
			type = "R_PAREN";
		else if (tmp->type == CMD)
			type = "COMMAND";
		// else if (tmp->type == DOLLAR)
		// 	type = "DOLLAR";
		else if (tmp->type == OR)
			type = "OR";
		else if (tmp->type == AND)
			type = "AND";
		else if (tmp->type == HEREDOC)
			type = "HEREDOC";
		else if (tmp->type == OUTPUT_APPEND)
			type = "OUTPUT_APPEND";
		else if (tmp->type == SUB_SHELL)
			type = "SUB_SHELL";
		else if (tmp->type == FILE_NAME)
			type = "FILE_NAME";
		ft_printf("type: %s, lexema: %s\n", type, tmp->lexema);
		tmp = tmp->next;
	}
}