/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 09:50:41 by cnatanae          #+#    #+#             */
/*   Updated: 2024/06/07 10:22:12 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	test_hello_world(t_envp **envp)
{
	char	*expected;
	char	*result;
	int		status;
	int		fd;
	int		old_fd;
	t_token	*tokens;
	t_token	*expr;

	result = allocate(14 * sizeof(char));
	tokens = create_with_enum(3, WORD, WORD, WORD);
	tokens->lexema = "echo";
	tokens->next->lexema = "Hello,";
	tokens->next->next->lexema = "World!";
	expr = cmd_parsing(tokens, envp);

	expected = allocate(14 * sizeof(char));
	expected = "Hello, World!";

	old_fd = dup(STDOUT_FILENO);
	fd = open("test_hello_world", O_CREAT | O_RDWR | O_TRUNC, 0644);

	dup2(fd, STDOUT_FILENO);
	status = execute(expr, envp);
	dup2(old_fd, STDOUT_FILENO);
	close(old_fd);
	close(fd);
	fd = open("test_hello_world", O_RDWR, 0644);
	result	= get_next_line(fd);
	typetree_insert(result);
	close(fd);
	return (is_equal_str(expected, result));
}

int	test_echo_pipe(t_envp **envp)
{
	char	*expected;
	char	*result;
	int		status;
	int		fd;
	int		old_fd;
	t_token	*tokens;
	t_token	*expr;

	old_fd = dup(STDOUT_FILENO);
	result = allocate(14 * sizeof(char));
	tokens = create_with_enum(5, WORD, WORD, WORD, PIPE, WORD);
	tokens->lexema = "echo";
	tokens->next->lexema = "hello,";
	tokens->next->next->lexema = "World!";
	tokens->next->next->next->next->lexema = "wc";
	expr = cmd_parsing(tokens, envp);

	expected = allocate(24 * sizeof(char));
	expected = "      1       2      14";

	fd = open("test_echo_pipe", O_CREAT | O_RDWR | O_TRUNC, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	status = execute(expr, envp);
	dup2(old_fd, STDOUT_FILENO);
	close(old_fd);
	fd = open("test_echo_pipe", O_RDWR, 0644);
	result	= get_next_line(fd);
	typetree_insert(result);
	close(fd);
	close(3);
	return (is_equal_str(expected, result));
}
