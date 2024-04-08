/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:53:15 by cnatanae          #+#    #+#             */
/*   Updated: 2023/12/06 13:03:02 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_build_string(t_listgnl *struc)
{
	int		idx;
	char	*line;
	size_t	size_lk;
	t_char	*aux;

	idx = 0;
	size_lk = ft_lstsize_gnl(struc->string, struc);
	line = malloc(sizeof(char) * size_lk + 2);
	if (!line)
		return (free_all(&struc->string));
	while (struc->string && struc->string->character != '\n')
	{
		aux = struc->string;
		line[idx++] = struc->string->character;
		struc->string = struc->string->next;
		free (aux);
	}
	aux = struc->string;
	if (struc->string)
		struc->string = struc->string->next;
	if (aux && aux->character == '\n')
		line[idx++] = '\n';
	free (aux);
	line[idx] = '\0';
	return (line);
}

int	ft_validation(t_listgnl *struc)
{
	while (struc->pos <= BUFFER_SIZE)
		struc->buffer[struc->pos++] = '\0';
	struc->read = read(struc->fd, struc->buffer, BUFFER_SIZE);
	struc->pos = 0;
	if (struc->read == -1)
	{
		free(struc->buffer);
		free_all(&struc->string);
		return (1);
	}
	return (0);
}

char	*ft_add_lk(t_listgnl *struc)
{
	t_char	*aux;

	aux = struc->string;
	while (aux && aux->next)
		aux = aux->next;
	while (struc->exist_n == 0 && struc->buffer[struc->pos] != '\0')
	{
		while (struc->buffer[struc->pos])
		{
			aux = add_node_to_end(struc, aux, struc->buffer[struc->pos++]);
			if (!aux)
				return (NULL);
		}
		struc->pos = 0;
		struc->exist_n = ft_find_n(struc);
		if (struc->exist_n == 0)
		{
			if (ft_validation(struc))
				return (NULL);
		}
	}
	return (ft_build_string(struc));
}

char	*get_next_line(int fd)
{
	static t_listgnl	struc[1024];
	char				*line;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	struc[fd].pos = 0;
	struc[fd].fd = fd;
	struc[fd].buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while (struc[fd].pos <= BUFFER_SIZE)
		struc[fd].buffer[struc[fd].pos++] = '\0';
	struc[fd].pos = 0;
	struc[fd].read = read(fd, struc[fd].buffer, BUFFER_SIZE);
	struc[fd].exist_n = 0;
	if (struc[fd].read == -1 || !struc[fd].buffer
		|| (!struc[fd].string && struc[fd].buffer[struc[fd].pos] == '\0'))
	{
		free(struc[fd].buffer);
		return (free_all(&struc[fd].string));
	}
	struc[fd].buffer[struc[fd].read] = '\0';
	line = ft_add_lk(&struc[fd]);
	free(struc[fd].buffer);
	return (line);
}
