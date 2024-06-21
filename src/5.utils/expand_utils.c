/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 17:36:02 by krocha-h          #+#    #+#             */
/*   Updated: 2024/06/21 17:36:38 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file expand_utils.c
 * @brief This file contains the pwd function
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/06/01
*/

#include "minishell.h"

char	*create_line(char **dst)
{
	char	*line;

	if (*dst)
	{
		line = ft_strdup(*dst);
		typetree_insert(line);
	}
	else
	{
		line = ft_strdup("");
		typetree_insert(line);
	}
	return (line);
}

char	*line_join(char *line, char *key, t_envp *envp)
{
	line = ft_strjoin(line, envp_get(key, envp));
	typetree_insert(line);
	return (line);
}
