/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:01:14 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/20 17:00:36 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief This function expands the environment variables
 * @param envp the environment variables
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/06/04
*/

#include "minishell.h"

int	is_valid_var(char letter)
{
	return ((letter >= 'a' && letter <= 'z')
		|| (letter >= 'A' && letter <= 'Z')
		|| (letter >= '0' && letter <= '9')
		|| letter == '_' || letter == '?');
}

void	expander_validation(t_data **data, char **cmd)
{
	int		flag;
	int		idx;
	int		odx;
	char	*line;

	line = NULL;
	flag = 0;
	odx = 0;
	while (cmd && cmd[odx])
	{
		idx = 0;
		while (cmd[odx] && cmd[odx][idx])
		{
			if (cmd[odx][idx] == '\'' && (flag == 0 || flag == 1))
				flag = ternary(flag == 0, 1, 0);
			else if (cmd[odx][idx] == '\"' && (flag == 0 || flag == 2))
				flag = ternary(flag == 0, 2, 0);
			else if (cmd[odx][idx] == '$' && flag != 1 && cmd[odx][idx + 1] && is_valid_var(cmd[odx][idx + 1]))
				expander(&idx, &cmd[odx],(*data)->my_envp, &line);
			else
				add_char(&line, cmd[odx][idx]);
			idx++;
		}
		cmd[odx] = line;
		line = "";
		odx++;
	}
}

void	expander(int *idx, char **cmd,t_envp *envp, char **dst)
{
	char	*line;
	char	*key;
	int		size;

	line = NULL;
	key = NULL;
	if (!cmd || !(*cmd)
		|| ft_isdigit((*cmd)[*(idx) + 1])
		|| (*cmd)[*(idx) + 1] == '$')
		return ;
	if (*dst)
	{
		line = ft_strdup(*dst);
		typetree_insert(line);
	}
	(*idx)++;
	size = *idx;
	while ((*cmd) && (*cmd)[size]
		&& is_valid_var((*cmd)[size]))
	{
		if ((*cmd)[size - 1] == '$' && (*cmd)[size] == '?' && size == (*idx))
		{
			size++;
			break ;
		}
		size++;
	}
	key = ft_substr(*cmd, (*idx), size - (*idx));
	typetree_insert(key);
	if (!line)
	{
		line = ft_strdup("");
		typetree_insert(line);
	}
	line = ft_strjoin(line, envp_get(key, envp));
	typetree_insert(line);
	if ((*cmd)[size] == '?')
		size++;
	*idx = size - 1;
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
