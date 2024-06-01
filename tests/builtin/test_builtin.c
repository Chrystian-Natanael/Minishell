/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 15:10:23 by krocha-h          #+#    #+#             */
/*   Updated: 2024/06/01 18:08:38 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include <stdio.h>

int	main()
{
	pwd();
	
	char	*args[3];
	
	args[0] = "echo";
	args[1] = "Kelly";
	args[2] = "Hayd";
	args[3] = '\0';
	
	echo(args);
	return (0);
}