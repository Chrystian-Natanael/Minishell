/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 19:50:30 by cnatanae          #+#    #+#             */
/*   Updated: 2024/05/01 18:17:03 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file utils.c
 * @brief This file contains the utils functions
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/04/27
*/

#include "minishell.h"

char	*get_username(t_envp *envp)
{
	char	*username;
	char	*final_string;
	char	*pwd;
	char	*str1;
	char	*str2;

	username = envp_get("USER", envp);
	pwd = envp_get("PWD", envp);
	if (!username)
		username = "minishell";
	str2 = ft_strrchr(pwd, '/');
	if (!str2)
		str2 = "//";
	str1 = ft_strjoin(++str2, "$\033[0m ");
	str2 = ft_strjoin("\033[92m", username);
	typetree_insert(str2);
	str2 = ft_strjoin(str2, "\033[0m:\033[34m");
	final_string = ft_strjoin(str2, str1);
	typetree_insert(final_string);
	typetree_insert(str2);
	typetree_insert(str1);
	return (final_string);
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

void	print_tokens(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		ft_printf("type: %d, lexema: %s\n", tmp->type, tmp->lexema);
		tmp = tmp->next;
	}
}

int	is_metacharacter(char a, char b)
{
	if (a == '|' || a == '(' || a == ')' || a == '<' || a == '>')
		return (1);
	else if (a == '&' && b == '&')
		return (1);
	return (0);
}

void	lst_addnew(t_token **list, enum e_token type, char *lexema)
{
	t_token	*new;
	t_token	*tmp;

	tmp = *list;
	new = malloc(sizeof(t_token));
	new->type = type;
	new->lexema = lexema;
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
