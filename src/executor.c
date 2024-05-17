/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:44:27 by cnatanae          #+#    #+#             */
/*   Updated: 2024/05/16 21:48:07 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file executor.c
 * @brief This file contains the executor functions
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/05/06
*/

#include "minishell.h"

// tudo isso pra começar a expansão de variável. Foi o Daniel que me obrigou :)
// segundo ele, eu que o obriguei a me obrigar (deu certo!)
// sinais vão ser resolvidos mais pro final. achei confuso colocar agora
// beijos e até logo!


// int	exec_cmd(t_bin *bin, t_envp *envp)
// {
// 	int		pid;
// 	int		return_code;
// 	int		counter[2];
// 	char	**args;
// 	char	*command;

// 	pid = fork();
// 	counter[1] = 0;
// 	if (pid == 0)
// 	{
// 		counter[0] = token_lst_size(bin->args);
// 		args = allocate((counter[0] + 1) * sizeof(char *));
// 		args[counter[0]] = NULL;
// 		while (counter[1] < counter[0])
// 		{
// 			args[counter[1]] = expand_var(get_node_index(bin->args, counter[1]), envp);
// 			counter[1]++;
// 		}
// 	}
// 	waitpid(pid, &return_code, 0);
// 	return_code = (return_code >> 8) & 0xFF;
// 	return (return_code);
// }

// int	exec_or(t_bin *bin, t_envp *envp)
// {
// 	int	status;

// 	status = exec_cmd(bin->left, envp);
// 	if (status != 0)
// 		status = exec_cmd(bin->right, envp);
// 	return (status);
// }

// int	exec_and(t_bin *bin, t_envp *envp)
// {
// 	int	status;

// 	status = exec_cmd(bin->left, envp);
// 	if (status == 0)
// 		status = exec_cmd(bin->right, envp);
// 	return (status);
// }

// int	exec_tree(t_bin *bin, t_envp *envp)
// {
// 	if (bin->type == CMD)
// 		return (exec_cmd(bin, envp));
// 	else if (bin->type == AND)
// 		return (exec_and(bin, envp));
// 	else if (bin->type == OR)
// 		return (exec_or(bin, envp));
// }

void	execute(t_token *tokens, t_envp *envp)
{
	int		status;
	t_bin	*bin;

	bin = create_binary(tokens, envp);

	// status = exec_tree(bin, envp); -- execução da árvore
}

t_bin	*create_binary(t_token *tokens, t_envp *envp)
{
	t_bin	*bin;

	bin = (t_bin *)allocate(sizeof(t_bin));
	if (bin == NULL)
	{
		ft_printf("\033[91mError: \033[0mMalloc failed\n");
		quit(1);
	}
	create_root(&bin, tokens);
	create_tree(tokens, bin, envp);
	return (bin);
}

void	create_root(t_bin **bin, t_token *tokens)
{
	t_token	*address;
	t_token	*tmp;

	tmp = tokens;
	address = NULL;
	while (tmp)
	{
		if (tmp->type == AND || tmp->type == OR)
			address = tmp;
		tmp = tmp->next;
	}
}
