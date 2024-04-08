/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnatanae <cnatanae@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 09:19:52 by cnatanae          #+#    #+#             */
/*   Updated: 2023/12/06 12:37:07 by cnatanae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

# define OFF 0
# define ON 1
# define BASE_DEC "0123456789"
# define BASE_HEXA 16
# define NULL_PTR "(nil)"
# define NULL_STR "(null)"
# define FLAGS "+ #"

typedef long long			t_lolo;
typedef unsigned long long	t_unlolo;
typedef unsigned int		t_uni;

/**@brief funciton to print a character or string or number or pointer.
 * 
 * @param format The string to be printed.
 * @param ... The argument list.
 * @return int The number of characters printed.
*/
int	ft_printf(const char *format, ...);

/**@brief Function to redirect the argument list to the correct function.
 * 
 * @param specifier The specifier.
 * @param ap The argument list.
 * @return int The number of characters printed.
*/
int	ft_parse(char specifier, va_list ap);

/**@brief Functon to verify if exists a flag (+ #).
 * 
 * @param format The string to be printed.
 * @param ap The argument list.
 * @return int The number of characters printed.
*/
int	ft_flag_check(const char *format, va_list ap);

/**@brief Function to treat the flag # (hash).
 * 
 * @param format The string to be printed.
 * @param ap The argument list.
 * @return int The number of characters printed.
*/
int	ft_hash(const char *format, va_list ap);

/**@brief Function to treat the flag + (plus).
 * 
 * @param format The string to be printed.
 * @param ap The argument list.
 * @return int The number of characters printed.
*/
int	ft_plus(const char *format, va_list ap);

/**@brief Function to print a pointer address.
 * 
 * @param pointer The pointer to be printed.
 * @param prefix The prefix to be printed.
 * @return int The number of characters printed.
*/
int	ft_put_ptr(unsigned long long pointer, int prefix);

/**@brief Function to treat the flag ' ' (space) in a specifier s.
 * 
 * @param format The string to be printed.
 * @param ap The argument list.
 * @return int The number of characters printed.
*/
int	ft_space_s(const char *format, va_list ap);

/**@brief Function to treat the flag ' ' (space).
 * 
 * @param format The string to be printed.
 * @param ap The argument list.
 * @return int The number of characters printed.
*/
int	ft_space(const char *format, va_list ap);

/**@brief Function to verify if exist a % in the string.
 * 
 * @param format The string to be printed.
 * @param ap The argument list.
 * @return int The number of characters printed.
*/
int	ft_print_build(const char *format, va_list ap);

#endif