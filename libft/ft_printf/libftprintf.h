/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:16:37 by saguesse          #+#    #+#             */
/*   Updated: 2022/09/09 14:54:10 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H
# include <ctype.h>
# include <stdio.h>
# include <string.h>
# include <strings.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

int		ft_printf(const char *format, ...);
int		ft_putchar(char c);
int		ft_putstr(char *s);
int		ft_putnbr(int n);
int		ft_putnbr_unsigned(unsigned int n);
int		ft_putnbr_hexa(size_t nb, char *base);
int		check_if_null(size_t nb);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);

#endif
