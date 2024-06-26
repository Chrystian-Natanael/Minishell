/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sub_shell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:06:21 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/21 20:38:51 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief This function executes a subshell
 * @param bin the binary tree node
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/06/03
*/

#include "minishell.h"

int	exec_sub_shell(t_bin *bin, t_data **data)
{
	int		status;
	int		pid;
	char	*new_line;
	t_token	*token;
	t_token	*expr;

	new_line = allocate(ft_strlen(bin->cmd) - 1);
	(void)ft_strlcpy(new_line, bin->cmd + 1, ft_strlen(bin->cmd) - 2);
	pid = fork();
	if (pid == 0)
	{
		token = lexer(new_line);
		if (new_line[0] == '\0' || token == NULL || syntax_error(token))
			ending (1);
		expr = cmd_parsing(token);
		if (syntax_expr(expr) != 0)
			return (syntax_expr(expr));
		ending(execute(expr, *data));
	}
	waitpid(pid, &status, 0);
	return ((status >> 8) & 0xFF);
}
