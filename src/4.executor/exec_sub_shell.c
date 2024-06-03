/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sub_shell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:06:21 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/03 15:20:16 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function executes a subshell
 * @param bin the binary tree node
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/06/03
*/

int	exec_sub_shell(t_bin *bin, t_envp **envp)
{
	int		status;
	char	*new_line;
	t_token	*token;
	t_token	*expr;

	new_line = allocate(ft_strlen(bin->cmd) - 1);
	(void)ft_strlcpy(new_line, bin->cmd + 1, ft_strlen(bin->cmd) - 2);
	token = lexer(new_line);
	if (new_line[0] == '\0' || token == NULL || syntax_error(token))
		return (1);
	expr = cmd_parsing(token);
	status = execute(expr, envp);
	return (status);
}