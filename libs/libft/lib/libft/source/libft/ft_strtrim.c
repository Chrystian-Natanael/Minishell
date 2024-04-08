/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:53:17 by cnatanae          #+#    #+#             */
/*   Updated: 2023/10/25 16:51:09 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_comp(char c, char const *set)
{
	int	idx;

	idx = 0;
	while (set[idx])
	{
		if (c == set[idx])
		{
			return (1);
		}
		idx++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		idx;
	char	*nstr;

	end = ft_strlen(s1);
	start = 0;
	idx = 0;
	while (ft_comp(s1[start], set))
		start++;
	while (ft_comp(s1[end - 1], set) && end > 0)
		end--;
	if (start >= end)
		return ((char *)ft_calloc(1, sizeof(char)));
	nstr = (char *)ft_calloc(1, sizeof(char) * (end - start + 1));
	if (!nstr)
		return (NULL);
	while (start < end)
		nstr[idx++] = s1[start++];
	return (nstr);
}
