/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 20:38:53 by krocha-h          #+#    #+#             */
/*   Updated: 2024/06/19 17:35:25 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file export.c
 * @brief This file contains the export function
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/06/01
*/

#include "minishell.h"

void	export_env(t_envp **envp, char *str)
{
	int		key_size;
	t_envp	*curr;

	curr = allocate(sizeof(t_envp));
	key_size = find_key_size(str);
	curr->key = ft_substr(str, 0, key_size);
	typetree_insert(curr->key);
	if (!ft_strchr(str, '='))
	{
		curr->value = NULL;
		curr->next = *envp;
		*envp = curr;
		return ;
	}
	curr->value = ft_substr(str, (key_size + 1), \
	(ft_strlen(str) - key_size - 1));
	typetree_insert(curr->value);
	curr->next = *envp;
	*envp = curr;
}

int	check_and_replace_env(char *str, t_envp **envp)
{
	t_envp	*curr;
	char	*key_to_find;
	char	*new_value;
	int		size;

	if (!ft_strchr(str, '='))
		return (0);
	size = ft_strchr(str, '=') - str;
	key_to_find = ft_strndup(str, size);
	new_value = ft_strdup(&str[size + 1]);
	typetree_insert(new_value);
	typetree_insert(key_to_find);
	curr = *envp;
	while (curr)
	{
		if (ft_strcmp(key_to_find, curr->key) == 0)
		{
			curr->value = new_value;
			return (1);
		}
		curr = curr->next;
	}
	return (0);
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
			return (ft_error("minishell: export: `", str, \
			"': not a valid identifier", 0));
		i++;
	}
	return (1);
}

void	export_print_envp(t_envp **envp)
{
	char	**sorted_envp;
	int		i;

	i = 0;
	sorted_envp = sort_envp(envp);
	while (sorted_envp[i])
	{
		if (ft_strncmp(sorted_envp[i], "?", 1))
			ft_printf("declare -x %s\n", sorted_envp[i]);
		i++;
	}
	free_split(sorted_envp);
}

int	ft_export(char **argv, t_envp **envp)
{
	int	i;

	i = 1;
	if (!argv[1])
	{
		export_print_envp(envp);
		return (0);
	}
	else
	{
		while (argv[i])
		{
			if (!validate_var(argv[i]))
				return (1);
			if (!check_and_replace_env(argv[i], envp))
				export_env(envp, argv[i]);
			i++;
		}
	}
	return (0);
}
