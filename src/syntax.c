/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:41:15 by cnatanae          #+#    #+#             */
/*   Updated: 2024/05/10 20:35:49 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file syntax.c
 * @brief This file contains the syntax functions
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/05/10
*/

#include "minishell.h"

int	syntax_error(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (!tmp)
		return (1);
	if (tmp->type == PIPE)
		return (1);
	if (tmp->type == OR)
		return (1);
	if (tmp->type == AND)
		return (1);
	while (tmp)
	{
		if (tmp->type == PIPE && !tmp->next)
			return (1);
		if (tmp->type == OR && !tmp->next)
			return (1);
		if (tmp->type == AND && !tmp->next)
			return (1);
		if (tmp->type == REDIR_INPUT && !tmp->next)
			return (1);
		if (tmp->type == REDIR_OUTPUT && !tmp->next)
			return (1);
		if (tmp->type == OUTPUT_APPEND && !tmp->next)
			return (1);
		if (tmp->type == HEREDOC && !tmp->next)
			return (1);
		if (tmp->type == L_PAREN && !tmp->next)
			return (1);
		if (tmp->type == REDIR_INPUT && tmp->next->type != WORD)
			return (1);
		if (tmp->type == REDIR_OUTPUT && tmp->next->type != WORD)
			return (1);
		if (tmp->type == OUTPUT_APPEND && tmp->next->type != WORD)
			return (1);
		if (tmp->type == HEREDOC && tmp->next->type != WORD)
			return (1);
		if (tmp->type == PIPE && (tmp->next->type != WORD && tmp->next->type != L_PAREN))
			return (1);
		if (tmp->type == OR && (tmp->next->type != WORD && tmp->next->type != L_PAREN))
			return (1);
		if (tmp->type == AND && (tmp->next->type != WORD && tmp->next->type != L_PAREN))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	organize_expressions(t_token **expr)
{
	t_token *tmp;

	tmp = *expr;
	while (tmp)
	{
		if (exist_redir(tmp->lexema))
			tmp->lexema = organize_redir(tmp->lexema);
		tmp = tmp->next;
	}
}

int	exist_redir(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<')
			return (1);
		i++;
	}
	return (0);
}

char	*organize_redir(char *str)
{
	char	*new_str;
	char	*tmp;
	char	*aux;
	int		i;

	i = 0;
	new_str = allocate(sizeof(char) * (ft_strlen(str) + 1));
	tmp = NULL; 	// ! echo oi > file.txt amor == echo oi amor > file.txt
	while (str[i]) // ! echo oi > file.txt amor > a.txt == echo oi amor > file.txt > a.txt
	{
		if (str[i] == '>' || str[i] == '<')
		{
			if (tmp == NULL)
			{
				tmp = ft_substr(str, i++, 1);
				typetree_insert(tmp);
				tmp = ft_strjoin(" ", tmp);
				typetree_insert(tmp);
			}
			else
			{
				tmp = ft_strjoin(tmp, " ");
				typetree_insert(tmp);
				aux = ft_substr(str, i++, 1);
				typetree_insert(aux);
				tmp = ft_strjoin(tmp, aux);
				typetree_insert(tmp);
			}
			if (str[i] == '>' || str[i] == '<')
			{
				aux = ft_substr(str, i++, 1);
				typetree_insert(aux);
				tmp = ft_strjoin(tmp, aux);
				typetree_insert(tmp);
			}
			tmp = ft_strjoin(tmp, " ");
			typetree_insert(tmp);
			while (ft_isspace(str[i]))
				i++;
			while (str[i] != '\0' && str[i] != ' ')
			{
				aux = ft_substr(str, i, 1);
				typetree_insert(aux);
				tmp = ft_strjoin(tmp, aux);
				typetree_insert(tmp);
				i++;
			}
		}
		else
		{
			aux = ft_substr(str, i, 1);
			typetree_insert(aux);
			new_str = ft_strjoin(new_str, aux);
			typetree_insert(new_str);
		}
		i++;
	}
	if (tmp != NULL)
	{
		new_str = ft_strjoin(new_str, tmp);
		typetree_insert(new_str);
	}
	return (new_str);
}
