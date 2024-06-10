/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 17:35:36 by krocha-h          #+#    #+#             */
/*   Updated: 2024/06/10 10:27:10 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file cd.c
 * @brief This file contains the echo function
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/06/01
*/

#include "minishell.h"

void	update_oldpwd(t_envp **envp)
{
	char	cwd[PATH_MAX];
	t_envp	*curr;
	t_envp	*new;

	curr = *envp;
	new = NULL;
	if (getcwd(cwd, PATH_MAX))
	{
		while(curr)
		{
			if (ft_strcmp("OLDPWD", curr->key) == 0)
			{
				free(curr->value);
				curr->value = ft_strdup(cwd);
				return ;
			}
			curr = curr->next;
		}
		new->key = ft_strdup("OLDPWD");
		new->value = ft_strdup(cwd);
		new->next = *envp;
		*envp = new;
	}
}

char	*find_path(char *dest, t_envp **envp)
{
	t_envp	*curr;
	char	*path;

	curr = *envp;
	while (curr)
	{
		if (ft_strcmp(dest, curr->key) == 0)
		{
			path = ft_strdup(curr->value);
			return (path);
		}
		curr = curr->next;
	}
	return (NULL);
}

int	go_to_path(int dest, char *arg, t_envp **envp)
{
	int	exit_status;

	exit_status = 0;
	if (dest == 0)
	{
		arg = find_path("HOME", envp);
		if (!arg)
			return (ft_putstr_fd("-minishell: cd: HOME not set\n", 2), 1);
	}
	else if (dest == 1)
	{
		arg = find_path("OLDPWD", envp);
		if (!arg)
			return (ft_putstr_fd("-minishell: cd: OLDPWD not set\n", 2), 1);
		else
		{
			ft_putstr_fd(arg, 1);
			ft_putstr_fd("\n", 1);
		}
	}
	update_oldpwd(envp);
	exit_status = chdir(arg);
	free(arg);
	return (exit_status);
}
# include <errno.h> // ! Essa biblioteca nn é permitida
int	ft_cd(char **argv, t_envp **envp)
{
	int	exit_status;
	char	*arg_one;

	exit_status = 0;
	if (argv[1])
		arg_one = ft_strdup(argv[1]);
	if (argv[2])
	{
		ft_putstr_fd("-minishell: cd: too many arguments\n", 2);
		return (1);
	}
	else if (!argv[1] || (ft_strcmp(argv[1], "~") == 0) || !argv)
		exit_status = go_to_path(0, NULL, envp);
	else if (ft_strcmp(argv[1], "-") == 0)
		exit_status = go_to_path(1, NULL, envp);
	else
		exit_status = go_to_path(2, argv[1], envp);
	if (exit_status < 0)
	{
		ft_putstr_fd("-minishell: cd: ", 2);
		ft_putstr_fd(arg_one, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit_status = 1;
	}
	return (exit_status);
}
