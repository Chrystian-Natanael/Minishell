/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 19:50:30 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/20 16:22:26 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file utils_1.c
 * @brief This file contains the utils functions
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/04/27
*/

#include "minishell.h"

void	lst_addnew(t_token **list, enum e_token type, char *lexeme)
{
	t_token	*new;
	t_token	*tmp;

	tmp = *list;
	new = allocate(sizeof(t_token));
	new->type = type;
	new->lexeme = lexeme;
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

void	lstadd_back(t_token **lst, t_token *new)
{
	t_token	*aux;

	aux = *lst;
	if (aux == NULL)
	{
		*lst = new;
		return ;
	}
	while (aux->next)
		aux = aux->next;
	aux->next = new;
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

int	args_count(char **argv)
{
	int	count;

	count = 0;
	while (argv[count])
		count++;
	return (count);
}

int	find_key_size(char *str)
{
	int	size;

	size = 0;
	while (str[size] && str[size] != '=')
		size++;
	return (size);
}

void	change_status(t_envp **envp, int status)
{
	char	*status_str;
	t_envp	*curr;

	curr = *envp;
	while (curr)
	{
		if (ft_strcmp(curr->key, "?") == 0)
		{
			status_str = ft_itoa(status);
			typetree_insert(status_str);
			curr->value = status_str;
			return ;
		}
		curr = curr->next;
	}
}
