/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 18:11:32 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/03 08:33:19 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file envp.c
 * @brief This file contains the envp functions
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/04/27
*/

#include "minishell.h"

t_envp	*create_envp(char **envp)
{
	int				i;
	char			**split;
	static t_envp	*my_envp;

	i = 0;
	while (envp[i])
	{
		split = ft_split(envp[i], '=');
		typetree_insert_matrix((void **)split);
		typetree_insert(split);
		if (count_envp(split) > 2)
			value_concat(split);
		if (split[0] && split[1])
			envp_insert(split[0], split[1], &my_envp);
		i++;
	}
	return (my_envp);
}

void	value_concat(char **split)
{
	int		i;
	char	*value;

	i = 1;
	value = ft_strdup(split[i]);
	typetree_insert(value);
	while (split[++i])
	{
		value = ft_strjoin(value, "=");
		typetree_insert(value);
		value = ft_strjoin(value, split[i]);
		typetree_insert(value);
	}
	split[1] = value;
}

int	count_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

void	envp_insert(char *key, char *value, t_envp **envp)
{
	t_envp	*new;
	t_envp	*current;

	new = (t_envp *)allocate(sizeof(t_envp));
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	typetree_insert(new->key);
	typetree_insert(new->value);
	new->next = NULL;
	if (!*envp)
	{
		*envp = new;
		return ;
	}
	current = *envp;
	while (current->next)
		current = current->next;
	current->next = new;
}

char	*envp_get(char *key, t_envp *envp)
{
	t_envp	*current;

	current = envp;
	while (current && current->next != NULL)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key)) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}
