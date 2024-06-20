/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_envp_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:07:00 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/20 17:12:58 by krocha-h         ###   ########.fr       */
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

	curr = *envp;
	if (cmd[0] == '/')
	{
		path = ft_strdup(cmd);
		typetree_insert(path);
		return (path);
	}
	while (curr)
	{
		if (ft_strncmp(curr->key, "PATH", 4) == 0)
			return (create_path(curr, cmd));
		curr = curr->next;
	}
	return (NULL);
}

char	*create_path(t_envp *envp, char *cmd)
{
	char	**split;
	char	*path;

	split = ft_split(envp->value, ':');
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
