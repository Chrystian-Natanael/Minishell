/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:43:56 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/20 14:29:38 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This file cotains functions utils
 * @author @Chrystian-Natanael
 * @date 2024/06/10
*/

void	clearscreen(void)
{
	printf("\033[H\033[J");
}

void	settextcolor(int color)
{
	printf("\033[%dm", color);
}

void	loadingbar(void)
{
	int			i;
	int			j;
	const int	length = 72;
	const char	*bar = "Bem vindo ao minishell!\nCriado por: \
		\nChrystian Natanael && Kelly Hayd";

	i = -1;
	while (++i <= length)
	{
		j = 0;
		clearscreen();
		settextcolor(96);
		printf("%-20s\n", bar + (length - i));
		printf("\n");
		while (j <= __INT_MAX__ / 80)
			j++;
	}
}

int	exist_content(char *str)
{
	int	equal;

	equal = 0;
	while (*str)
	{
		if (*str == '=')
			equal = 1;
		str++;
	}
	if (!equal)
		return (0);
	return (1);
}

int	ft_envp_size(t_envp *lst)
{
	int	size_list;

	size_list = 0;
	while (lst)
	{
		lst = lst->next;
		size_list++;
	}
	return (size_list);
}
