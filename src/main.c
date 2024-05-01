/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 08:19:03 by cnatanae          #+#    #+#             */
/*   Updated: 2024/05/01 08:39:06 by cnatanae         ###   ########.fr       */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_envp	*my_envp;
	char	*username;
	t_token	*token;

	(void)argc;
	(void)argv;
	my_envp = create_envp(envp);
	username = get_username(my_envp);
	line = readline(username);
	while (line)
	{
		if (line[0] != '\0')
			add_history(line);
		typetree_insert(line);
		line = readline(username);
		token = lexer(line);
		print_tokens(token);
	}
	rl_clear_history();
	ft_printf("\033[91mEnding Minishell\033[0m, \033[92mThanks!\033[0m\n");
	quit(0);
}
