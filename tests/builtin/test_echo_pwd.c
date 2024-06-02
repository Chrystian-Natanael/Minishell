/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_echo_pwd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 15:10:23 by krocha-h          #+#    #+#             */
/*   Updated: 2024/06/02 16:40:33 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	main()
{
	pwd();
	ft_putchar_fd('\n', 1);
	
	char	*echos[3];
	echos[0] = "echo";
	echos[1] = "Kelly";
	echos[2] = "Hayd";
	echos[3] = '\0';
	
	echo(echos);
	ft_putchar_fd('\n', 1);

	char	*exit[3];
	exit[0] = "exit";
	exit[1] = "12";
	exit[2] = "kelly";
	exit(exit);
	
	return (0);
}