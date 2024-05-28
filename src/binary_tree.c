/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:26:16 by cnatanae          #+#    #+#             */
/*   Updated: 2024/05/28 16:27:37 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function creates a new binary tree node
 * @param content The content of the new node
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/05/01
*/

int	precedence(enum e_token type)
{
	if (type == AND || type == OR)
		return (5);
	else if (type == PIPE)
		return (4);
	else if (type == REDIR_INPUT || type == REDIR_OUTPUT
		|| type == OUTPUT_APPEND || type == HEREDOC)
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
