/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:19:33 by saguesse          #+#    #+#             */
/*   Updated: 2022/10/06 12:44:22 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	arg_type(const char c, va_list args, int i)
{
	if (c == 'c')
		i += ft_putchar(va_arg(args, int));
	else if (c == 's')
		i += ft_putstr(va_arg(args, char *));
	else if (c == 'p')
		i += check_if_null(va_arg(args, long unsigned int));
	else if (c == 'i' || c == 'd')
		i += ft_putnbr(va_arg(args, int));
	else if (c == 'u')
		i += ft_putnbr_unsigned(va_arg(args, unsigned int));
	else if (c == 'x')
		i += ft_putnbr_hexa(va_arg(args, unsigned int), "0123456789abcdef");
	else if (c == 'X')
		i += ft_putnbr_hexa(va_arg(args, unsigned int), "0123456789ABCDEF");
	else if (c == '%')
		i += ft_putchar('%');
	return (i);
}

int	check_s(const char *s)
{	
	int	i;

	i = 0;
	if (!s)
		return (ft_putstr("Error: null format string\n"));
	while (s[i])
	{
		if (s[i] == '%')
		{
			i++;
			if (s[i] == '\0' || ft_strchr("cspdiuxX%", s[i]) == NULL)
				return (0);
		}
		i++;
	}
	return (1);
}

int	ft_printf(const char *s, ...)
{
	va_list	args;
	size_t	j;
	int		i;

	va_start(args, s);
	i = 0;
	if (check_s(s) == 0)
		return (ft_putstr("Error"));
	j = 0;
	while (j < ft_strlen(s))
	{
		if (s[j] == '%')
		{
			j++;
			i += arg_type(s[j], args, 0);
		}
		else
			i += ft_putchar(s[j]);
		j++;
	}
	va_end(args);
	return (i);
}
