/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 20:38:53 by krocha-h          #+#    #+#             */
/*   Updated: 2024/06/18 23:27:13 by krocha-h         ###   ########.fr       */
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

char	**create_envp_array(t_envp **envp)
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

void	export_print_envp(t_envp **envp)
{
	char	**sorted_envp;
	int		i;

	i = 0;
	sorted_envp = sort_envp(envp);
	while (sorted_envp[i])
	{
		ft_printf("declare -x %s\n", sorted_envp[i]);
		i++;
	}
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
			if (!validate_var(argv[i]) && !ft_strchr(argv[i], '='))
				return (1);
			if (!exist_content(argv[i]))
				return (0);
			if (!check_and_replace_env(argv[i], envp))
				export_env(envp, argv[i]);
			i++;
		}
	}
	return (0);
}
