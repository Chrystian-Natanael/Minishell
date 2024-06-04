/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:01:14 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/04 19:31:23 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function expands the environment variables
 * @param envp the environment variables
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/06/04
*/

int	is_valid_var(char letter)
{
	return ((letter >= 'a' && letter <= 'z')
		|| (letter >= 'A' && letter <= 'Z')
		|| (letter >= '0' && letter <= '9')
		|| letter == '_');
}

void	expander_validation(t_token **tokens, t_envp **envp)
{
	int	flag;
	int	idx;
	char	*line;
	t_token	*tmp;

	tmp = *tokens;
	while (tmp)
	{
		line = NULL;
		flag = 0;
		idx = 0;
		while (tmp && tmp->lexema && tmp->lexema[idx])
		{
			if (tmp->lexema[idx] == '\'' && (flag == 0 || flag == 1))
				flag = ternary(flag == 0, 1, 0);
			else if (tmp->lexema[idx] == '\"' && (flag == 0 || flag == 2))
				flag = ternary(flag == 0, 2, 0);
			else if (tmp->lexema[idx] == '$' && flag != 1)
				expander(&idx, &tmp, *envp, &line);
			else
				add_char(&line, tmp->lexema[idx]);
			idx++;
		}
		if (line)
			tmp->lexema = line;
		tmp = tmp->next;
	}
}

void	expander(int	*idx, t_token	**token, t_envp	*envp, char **dst)
{
	char	*line;
	char	*key;
	int		size;
	
	line = NULL;
	key = NULL;
	if (!(*token) || !(*token)->lexema || ft_isdigit((*token)->lexema[*(idx) + 1]) || (*token)->lexema[*(idx) + 1] == '$')
		return ;
	if ((*idx) != 0)
		line = ft_substr((*token)->lexema, 1, (*idx) - 1);
	typetree_insert(line);
	(*idx)++;
	size = *idx;
	while ((*token)->lexema && (*token)->lexema[size] && is_valid_var((*token)->lexema[size]))
		size++;
	key = ft_substr((*token)->lexema, (*idx), size - (*idx));
	typetree_insert(key);
	if (!line)
	{
		line = ft_strdup("");
		typetree_insert(line);
		size--;
	}
	line = ft_strjoin(line, envp_get(key, envp));
	typetree_insert(line);
	*idx = size;
	key = ft_substr((*token)->lexema, size, ft_strlen((*token)->lexema) - (size + 1));
	typetree_insert(key);
	line = ft_strjoin(line, key);
	typetree_insert(line);
	(*dst) = line;
}

void	add_char(char **line, char c)
{
	char	*tmp;
	int		i;

	i = 0;
	if (*line)
	{
		tmp = ft_strdup(*line);
		typetree_insert(tmp);
		*line = allocate(ft_strlen(tmp) + 2);
		while (tmp[i])
		{
			(*line)[i] = tmp[i];
			i++;
		}
		(*line)[i] = c;
		(*line)[i + 1] = '\0';
	}
	else
	{
		*line = allocate(2);
		(*line)[0] = c;
		(*line)[1] = '\0';
	}
}
