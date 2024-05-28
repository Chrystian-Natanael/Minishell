/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:44:27 by cnatanae          #+#    #+#             */
/*   Updated: 2024/05/28 15:55:58 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file executor.c
 * @brief This file contains the executor functions
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/05/06
*/

#include "minishell.h"

// tudo isso pra começar a expansão de variável. Foi o Daniel que me obrigou :)
// segundo ele, eu que o obriguei a me obrigar (deu certo!)
// sinais vão ser resolvidos mais pro final. achei confuso colocar agora
// beijos e até logo!


// int	exec_cmd(t_bin *bin, t_envp *envp)
// {
// 	int		pid;
// 	int		return_code;
// 	int		counter[2];
// 	char	**args;
// 	char	*command;

// 	pid = fork();
// 	counter[1] = 0;
// 	if (pid == 0)
// 	{
// 		counter[0] = token_lst_size(bin->args);
// 		args = allocate((counter[0] + 1) * sizeof(char *));
// 		args[counter[0]] = NULL;
// 		while (counter[1] < counter[0])
// 		{
// 			args[counter[1]] = expand_var(get_node_index(bin->args, counter[1]), envp);
// 			counter[1]++;
// 		}
// 	}
// 	waitpid(pid, &return_code, 0);
// 	return_code = (return_code >> 8) & 0xFF;
// 	return (return_code);
// }

// int	exec_or(t_bin *bin, t_envp *envp)
// {
// 	int	status;

// 	status = exec_cmd(bin->left, envp);
// 	if (status != 0)
// 		status = exec_cmd(bin->right, envp);
// 	return (status);
// }

// int	exec_and(t_bin *bin, t_envp *envp)
// {
// 	int	status;

// 	status = exec_cmd(bin->left, envp);
// 	if (status == 0)
// 		status = exec_cmd(bin->right, envp);
// 	return (status);
// }

// int	exec_tree(t_bin *bin, t_envp *envp)
// {
// 	if (bin->type == CMD)
// 		return (exec_cmd(bin, envp));
// 	else if (bin->type == AND)
// 		return (exec_and(bin, envp));
// 	else if (bin->type == OR)
// 		return (exec_or(bin, envp));
// }

static void	print_tree(t_bin *bin, int level);

void	execute(t_token *tokens, t_envp *envp)
{
	// int		status;
	t_bin	*bin;

	bin = create_tree(tokens);
	print_tree(bin, 0);
	if (envp == NULL || bin == NULL)
		return ;
	// status = exec_tree(bin, envp); -- execução da árvore
}

static void	print_tree(t_bin *bin, int level)
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
int	precedence(enum e_token type)
{
	if (type == AND || type == OR)
		return (5);
	else if (type == PIPE)
		return (4);
	else if (type == REDIR_INPUT || type == REDIR_OUTPUT || type == OUTPUT_APPEND || type == HEREDOC)
		return (3);
	else if (type == SUB_SHELL)
		return (2);
	else if (type == CMD)
		return (1);
	return (-1);
}

t_bin	*new_node(char *cmd, enum e_token type)
{
	t_bin	*node;

	node = allocate(sizeof(t_bin));
	if (!node)
		return (NULL);
	node->cmd = cmd;
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_bin	*create_tree(t_token *tokens)
{
	t_token	*curr;
	t_token	*max_prec;
	t_bin	*bin;
	t_token *left_list;
	t_token *right_list;
	int		max_prec_val;

	curr = tokens;
	max_prec = curr;
	if (!curr)
		return (NULL);
	max_prec_val = precedence(curr->type);
	while (curr)
	{
		if (precedence(curr->type) >= max_prec_val)
		{
			max_prec = curr;
			max_prec_val = precedence(curr->type);
		}
		curr = curr->next;
	}
	bin = new_node(max_prec->lexema, max_prec->type);

	if (max_prec->type != CMD)
	{
		left_list = return_token_list(tokens, max_prec);
		right_list = max_prec->next;
		bin->left = create_tree(left_list);
		bin->right = create_tree(right_list);
	}
	return (bin);
}

t_token	*return_token_list(t_token *tokens, t_token *max_prec)
{
	t_token	*tmp;
	t_token	*new;
	t_token	*left_list;

	tmp = tokens;
	left_list = NULL;
	while (tmp != max_prec)
	{
		new = allocate(sizeof(t_token));
		new->type = tmp->type;
		new->lexema = tmp->lexema;
		new->next = NULL;
		lstadd_back(&left_list, new);
		tmp = tmp->next;
	}
	return (left_list);
}



// << eof | cmd1 | cmd2 | (cmd3 || cmd4) && (cmd5 | (cmd6)) > out
// !									 * raiz
// !					| pipe
