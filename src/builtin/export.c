/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 20:38:53 by krocha-h          #+#    #+#             */
/*   Updated: 2024/06/01 22:12:26 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file pwd.c
 * @brief This file contains the pwd function
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/06/01
*/

#include "minishell.h"

void	export_env(t_envp **envp, char *str)
{
	int		i;
	int		j;
	t_envp	*curr;

	curr = allocate(sizeof(t_envp));
	i = 0;
	while (str[i] != '=')
	{
		curr->key[i] = str[i];
		i++;
	}
	curr->key[i] = '\0';
	i++;
	j = 0;
	while (str[i])
	{
		curr->value[j] = str[i];
		i++;
		j++;
	}
	curr->value[j] = '\0';
	curr->next = *envp;
}

int	validate_var(char *str)
{
	int		i;

	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[i] != '_' && !ft_isalnum(str[i]) && !ft_isalpha(str[i]))
			return (0);
		i++;
	}
	return  (1);
}

void	export_print_envp(t_envp **envp)
{
	t_envp	*curr;

	curr = *envp;
	while (curr)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(curr->key, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(curr->value, 1);
		ft_putstr_fd("\n", 1);
		curr = curr->next;
	}
}

int	ft_export(char **argv, t_envp **envp)
{
	int	i;

	i = 1;
	if (args_count(argv) == 1)
	{
		export_print_envp(envp);
		return (0);
	}
	else
	{
		while (argv[i])
		{
			if (!validate_var(argv[i]) && !ft_strchr(argv[i], '='))
				return (1);
			export_env(envp, argv[i]);
			i++;
		}
	}
}
