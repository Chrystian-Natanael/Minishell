/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:53:18 by cnatanae          #+#    #+#             */
/*   Updated: 2023/11/23 14:55:31 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

/**@brief Struct to store a character and a pointer to the next character.
 * 
 * @param character for the character.
 * @param *next the pointer to the next node.
*/
typedef struct s_char
{
	char			character;
	struct s_char	*next;
}					t_char;

/**@brief Struct to store a variable and a pointer to the next node.
 * 
 * @param fd The file descriptor.
 * @param pos The position of the buffer.
 * @param read The number of bytes read.
 * @param len The length of the struct s_list.
 * @param buffer The buffer.
 * @param *string The pointer to the next node.
*/
typedef struct s_listgnl
{
	int		fd;
	int		pos;
	int		read;
	int		len;
	int		exist_n;
	char	*buffer;
	t_char	*string;
}			t_listgnl;

/**@brief Function to get the next line.
 * 
 * @param fd The file descriptor.
 * @return char* The next line.
*/
char	*get_next_line(int fd);

/**@brief Function to clear the linked list.
 * 
 * @param *str The pointer to the linked list.
 * @return char* The pointer to NULL.
*/
void	*free_all(t_char **str);

/**@brief Function to create a new node and add character to it.
 * 
 * @param *str The character to be added.
 * @return t_char* The pointer to the new node.
*/
t_char	*ft_node(char c);

/**@brief Function to get the size of the linked list.
 * 
 * @param *lst The pointer to the linked list.
 * @param *struc The pointer to the struct t_listgnl.
 * @return int The size of the linked list.
*/
int		ft_lstsize_gnl(t_char *lst, t_listgnl *struc);

/**@brief Function to find the character '\n' in the linked list.
 * 
 * @param *struc The pointer to the struct t_listgnl.
 * @return int 1 if '\n' is found, 0 if not.
*/
int		ft_find_n(t_listgnl *struc);

/**@brief Function to build the string.
 * 
 * @param *struc The pointer to the struct t_listgnl.
 * @return char* The pointer to the string.
*/
char	*ft_build_string(t_listgnl *struc);

/**@brief Function to add the buffer to the linked list.
 * 
 * @param *struc The pointer to the struct t_listgnl.
 * @return char* The pointer to the string.
*/
char	*ft_add_lk(t_listgnl *struc);

/**@brief Function to add a new node to the end of the linked list.
 * 
 * @param *struc The pointer to the struct t_listgnl.
 * @param *end The pointer to the last node of the linked list.
 * @param c The character to be added.
 * @return t_char* The pointer to the new node.
*/
t_char	*add_node_to_end(t_listgnl *struc, t_char *end, char c);

#endif
