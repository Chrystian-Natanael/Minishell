/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:01:14 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/21 15:55:27 by krocha-h         ###   ########.fr       */
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

int	define_quote_flag(char **cmd, int *i, int flag, int *flag_g)
{
	if (cmd[i[1]][i[0]] == '\'' && (flag == 0 || flag == 1))
	{
		return (ternary(flag == 0, 1, 0));
		*flag_g = 1;
		return (1);
	}
	else if (cmd[i[1]][i[0]] == '\"' && (flag == 0 || flag == 2))
	{
		return (ternary(flag == 0, 2, 0));
		*flag_g = 1;
		return (1);
	}
	return (0);
}

void	expander_validation(t_data **data, char **cmd, int *flag_g)
{
	int		flag;
	int		i[2];
	char	*line;

	line = NULL;
	i[1] = -1;
	while (cmd && cmd[++i[1]])
	{
		i[0] = -1;
		flag = 0;
		while (cmd[i[1]] && cmd[i[1]][++i[0]])
		{
			if ((cmd[i[1]][i[0]] == '\'' && (flag == 0 || flag == 1))
				|| (cmd[i[1]][i[0]] == '\"' && (flag == 0 || flag == 2)))
				flag = define_quote_flag(cmd, i, flag, flag_g);
			// if (cmd[i[1]][i[0]] == '\'' && (flag == 0 || flag == 1))
			// {
			// 	flag = ternary(flag == 0, 1, 0);
			// 	*flag_g = 1;
			// }
			// else if (cmd[i[1]][i[0]] == '\"' && (flag == 0 || flag == 2))
			// {
			// 	flag = ternary(flag == 0, 2, 0);
			// 	*flag_g = 1;
			// }
			else if (cmd[i[1]][i[0]] == '$' && flag != 1 && cmd[i[1]][i[0] + 1]
				&& is_valid_var(cmd[i[1]][i[0] + 1]))
				expander(&i[0], &cmd[i[1]], (*data)->my_envp, &line);
			else
				add_char(&line, cmd[i[1]][i[0]]);
		}
		cmd[i[1]] = line;
		line = "";
	}
}

void	expander(int *idx, char **cmd, t_envp *envp, char **dst)
{
	char	*line;
	char	*key;
	int		size;

	line = NULL;
	key = NULL;
	if (!cmd || !(*cmd) || ft_isdigit((*cmd)[*(idx) + 1])
		|| (*cmd)[*(idx) + 1] == '$')
		return ;
	if (*dst)
	{
		line = ft_strdup(*dst);
		typetree_insert(line);
	}
	size = ++(*idx);
	while ((*cmd) && (*cmd)[size] && is_valid_var((*cmd)[size]))
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
