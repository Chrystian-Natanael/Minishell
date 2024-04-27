/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 18:11:32 by cnatanae          #+#    #+#             */
/*   Updated: 2024/04/27 19:30:38 by cnatanae         ###   ########.fr       */
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
		if (split[0] && split[1])
			envp_insert(split[0], split[1], &my_envp);
		i++;
		free_split(split);
	}
	return (my_envp);
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
