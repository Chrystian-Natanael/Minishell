/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 08:19:03 by cnatanae          #+#    #+#             */
/*   Updated: 2024/04/27 17:21:00 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;
	
	ft_printf("Welcome to Minishell, enjoy!\n");
	line = readline("minishell$: ");
	while (line)
	{
		if (line[0] != '\0')
			add_history(line);
		typetree_insert(line);
		line = readline("minishell$: ");
	}
	rl_clear_history();
	ft_printf("Ending Minishell, Thanks!\n");
	quit(0);
}
