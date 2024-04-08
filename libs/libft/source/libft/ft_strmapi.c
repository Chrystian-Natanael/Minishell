/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 10:46:18 by cnatanae          #+#    #+#             */
/*   Updated: 2023/11/09 14:17:11 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int				size;
	char			*nstr;
	unsigned int	idx;

	idx = 0;
	size = ft_strlen(s);
	nstr = (char *)ft_calloc(1, (sizeof (char)) * (size + 1));
	if (!nstr)
		return (NULL);
	while (s[idx])
	{
		nstr[idx] = f(idx, s[idx]);
		idx++;
	}
	nstr[idx] = '\0';
	return (nstr);
}
