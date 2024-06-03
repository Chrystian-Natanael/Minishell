/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_envp_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:07:00 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/03 14:14:09 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function gets the path of the command
 * @param cmd the command to be executed
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/06/03
*/

char	*get_path_cmd(t_envp **envp, char *cmd)
{
	t_envp	*curr;
	char	*path;
	char	**split;
	curr = *envp;
	while (curr)
	{
		if (ft_strncmp(curr->key, "PATH", 4) == 0)
		{
			split = ft_split(curr->value, ':');
			typetree_insert_matrix((void **)split);
			typetree_insert(split);
			while (*split)
			{
				path = ft_strjoin(*split, "/");
				typetree_insert(path);
				path = ft_strjoin(path, cmd);
				typetree_insert(path);
				if (access(path, F_OK) == 0)
					return (path);
				split++;
			}
			return (path);
		}
		curr = curr->next;
	}
	return (NULL);
}

char	**t_envp_to_char(t_envp **envp)
{
	t_envp	*curr;
	char	**envp_char;
	int		i;

	i = size_envp(envp);
	envp_char = allocate(sizeof(char *) * (i + 1));
	if (!envp_char)
		return (NULL);
	i = 0;
	curr = *envp;
	while (curr)
	{
		envp_char[i] = ft_strjoin(curr->key, "=");
		typetree_insert(envp_char[i]);
		envp_char[i] = ft_strjoin(envp_char[i], curr->value);
		typetree_insert(envp_char[i]);
		i++;
		curr = curr->next;
	}
	envp_char[i] = NULL;
	return (envp_char);
}

int	size_envp(t_envp **envp)
{
	t_envp	*curr;
	int		i;

	i = 0;
	curr = *envp;
	while (curr)
	{
		i++;
		curr = curr->next;
	}
	return (i);
}
