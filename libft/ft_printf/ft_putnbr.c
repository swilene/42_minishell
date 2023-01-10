/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 09:36:39 by saguesse          #+#    #+#             */
/*   Updated: 2022/06/01 18:07:56 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_putnbr(int n)
{
	int	i;

	i = 0;
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	else if (n < 0 && n > -2147483648)
	{
		i += ft_putchar('-');
		i += ft_putnbr(n * -1);
	}
	else if (n >= 0 && n <= 9)
		i += ft_putchar('0' + n);
	else
	{
		i += ft_putnbr(n / 10);
		i += ft_putnbr(n % 10);
	}
	return (i);
}
