/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 20:05:19 by krocha-h          #+#    #+#             */
/*   Updated: 2024/06/21 18:38:56 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file exit.c
 * @brief This file contains the exit function
 * @author @Chrystian-Natanael && @kellyhayd
 * @date 2024/06/01
*/

#include "minishell.h"

static int	check_number(char *str)
{
	char			*arg;
	size_t			len;
	const size_t	max_len = 19;

	if (!ft_isonlynum(str) && (str[0] != '-' && str[0] != '+'))
		return (0);
	arg = str;
	if (*arg && (*arg == '-' || *arg == '+'))
		arg++;
	while (*arg == '0')
		arg++;
	len = ft_strlen(arg);
	if (len < max_len)
		return (1);
	if (len > max_len)
		return (0);
	if (str[0] == '-')
		return (ft_strcmp(&MIN_NB[1], arg) >= 0);
	return (ft_strcmp(arg, &MAX_NB[0]) <= 0);
}

int	ft_exit(char **argv, t_data *data)
{
	int	count;

	count = args_count(argv);
	if (count == 1)
	{
		close_files(data);
		ending(0);
	}
	if (!check_number(argv[1]))
	{
		ft_error("exit: ", argv[1], ": numeric argument required\n", 2);
		close_files(data);
		ending(2);
	}
	else if (count > 2)
	{
		ft_putstr_fd("-minishell: exit: too many arguments\n", 2);
		return (1);
	}
	else if (count == 2)
	{
		close_files(data);
		ending(ft_atol(argv[1]));
	}
	return (0);
}

void	close_files(t_data *data)
{
	int	idx;
	char	*fl_name;

	idx = 1;
	while (idx <= data->count_files)
	{
		fl_name = ft_strmerge(ft_strdup("/tmp/heredoc-0x"), ft_itoa(idx));
		typetree_insert(fl_name);
		unlink(fl_name);
		idx++;
	}
}
