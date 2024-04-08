/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:04:28 by cnatanae          #+#    #+#             */
/*   Updated: 2023/10/16 13:25:33 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*nstr;
	int		idx_a;
	int		idx_b;

	idx_a = 0;
	idx_b = 0;
	nstr = (char *)malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 1));
	if (!nstr)
		return (NULL);
	while (s1[idx_a])
	{
		nstr[idx_b] = s1[idx_a];
		idx_a++;
		idx_b++;
	}
	idx_a = 0;
	while (s2[idx_a])
	{
		nstr[idx_b] = s2[idx_a];
		idx_a++;
		idx_b++;
	}
	nstr[idx_b] = '\0';
	return (nstr);
}
