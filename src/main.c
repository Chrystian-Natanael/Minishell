/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 08:19:03 by cnatanae          #+#    #+#             */
/*   Updated: 2024/04/27 19:30:00 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_username(t_envp *envp);

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_envp	*my_envp;
	char	*username;

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
	}
	rl_clear_history();
	ft_printf("\033[91mEnding Minishell\033[0m, \033[92mThanks!\033[0m\n");
	quit(0);
}

static char	*get_username(t_envp *envp) // ! por num utils depois
{
	char	*username;
	char	*str1;
	char	*str2;
	username = envp_get("USER", envp);
	if (!username)
		username = "minishell";
	str1 = ft_strjoin(username, "$: \033[0m");
	str2 = ft_strjoin("\033[92m", str1);
	typetree_insert(str1);
	typetree_insert(str2);
	return (str2);
}
