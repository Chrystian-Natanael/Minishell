/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:17:44 by cnatanae          #+#    #+#             */
/*   Updated: 2023/11/11 12:20:52 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c)
{
	int	words;

	words = 0;
	if (!s)
		return (0);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if ((*s != c) && *s)
			words++;
		while (*s != c && *s)
			s++;
	}
	return (words);
}

static int	ft_size(char *s, char c)
{
	int		i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

static char	*ft_put_letter(char *s, char c)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *)ft_calloc(1, sizeof(char) * ft_size(s, c) + 1);
	if (!str)
		return (NULL);
	while (s[i] != c && s[i])
	{
		str[i] = s[i];
		i++;
	}
	return (str);
}

void	ft_free(char **split)
{
	int	idx;

	idx = 0;
	while (split[idx])
		free(split[idx++]);
	free(split);
}

char	**ft_split(char const *s, char c)
{
	int		idx_b;
	char	**split;

	idx_b = 0;
	split = (char **)ft_calloc((ft_count_words(s, c) + 1), sizeof(char *));
	if (!split || !s)
		return (0);
	while (*s)
	{
		if (*s != c)
		{
			split[idx_b] = ft_put_letter((char *)s, c);
			if (!split[idx_b++])
			{
				ft_free(split);
				return (NULL);
			}
			while (*s != c && *s)
				s++;
		}
		else
			s++;
	}
	return (split);
}
