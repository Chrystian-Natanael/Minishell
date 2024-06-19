/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 10:45:10 by krocha-h          #+#    #+#             */
/*   Updated: 2024/06/19 10:46:06 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file export_utils.c
 * @brief This file contains the utils functions
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/06/19
*/

#include "minishell.h"

static char	**create_envp_array(t_envp **envp)
{
	char	**envp_array;
	int		size;
	int		i;
	t_envp	*curr;
	
	size = ft_envp_size(*envp);
	envp_array = malloc(sizeof(char*) * (size + 1));
	curr = *envp;
	i = 0;
	while (curr)
	{
		size = ft_strlen(curr->key) + ft_strlen(curr->value) + 2;
		envp_array[i] = ft_calloc(sizeof(char), size);
		ft_strlcpy(envp_array[i], curr->key, size);
		if (curr->value)
		{
			ft_strlcat(envp_array[i], "=", size);
			ft_strlcat(envp_array[i], curr->value, size);
		} 
		curr = curr->next;
		i++;
	}
	envp_array[i] = NULL;
	return (envp_array);
}

char	**sort_envp(t_envp **envp)
{
	char	**envp_array;
	char	*tmp;
	int		i;
	int		j;

	i = 1;
	tmp = NULL;
	envp_array = create_envp_array(envp);
	while (envp_array[i])
	{
		j = 0;
		while (j < i)
		{
			if (ft_strcmp(envp_array[j], envp_array[i]) > 0)
			{
				tmp = envp_array[i];
				envp_array[i] = envp_array[j];
				envp_array[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (envp_array);
}