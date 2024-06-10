/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:43:56 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/10 12:34:37 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/**
 * @brief This function frees the tokens
 * @param tokens the tokens to be freed
 * @author @Chrystian-Natanael
 * @date 2024/06/10
*/

void	clearScreen()
{
	printf("\033[H\033[J");
}

void	setTextColor(int color)
{
	printf("\033[%dm", color);
}

void	loadingBar()
{
	int	i;
	int	j;
	const char *bar1 = "Bem vindo ao minishell!";
	const char *bar2 = "Criado por:";
	const char *bar3 = "Chrystian Natanael && Kelly Hayd";
	const int length = 24;

	i = -1;
	while (++i <= length)
	{
		j = 0;
		clearScreen();
		setTextColor(96);
		printf("%-20s\n", bar1 + (length - i));
		printf("%-20s\n", bar2 + (length - i));
		printf("%-20s\n", bar3 + (length - i));
		printf("\n");
		while (j <= __INT_MAX__ / 80)
			j++;
	}

}
