/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   super_libft.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 08:46:57 by pledieu           #+#    #+#             */
/*   Updated: 2025/01/28 09:09:13 by pledieu          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUPER_LIBFT_H
# define SUPER_LIBFT_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

int		ft_printf(const char *format, ...);
int		ft_parse_format(char specifier, va_list args);
int		ft_handle_char(char c);
int		ft_handle_string(char *str);
int		ft_handle_int(int num);
int		ft_handle_hex(unsigned int num, int uppercase);
int		ft_handle_pointer(void *ptr);
int		ft_putchar(char c);
int		ft_putstr(char *str);
int		ft_handle_unsigned(unsigned int num);

char	*ft_itoa_unsigned(unsigned int num);
char	*ft_itoa_gnl(int n);
char	*ft_itoa_base(unsigned long num, int base, int uppercase);

char	*get_next_line(int fd);
char	*ft_strdup_gnl(const char *s1);
char	*ft_strjoin_gnl(char *s1, char *s2);
size_t	ft_strlen_gnl(const char *s);
int		ft_check_line(char *str);

#endif