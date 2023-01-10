/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:30:07 by saguesse          #+#    #+#             */
/*   Updated: 2022/06/02 14:28:22 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_putnbr_hexa(size_t nb, char *base)
{
	int	i;

	i = 0;
	if (nb < 16)
		i += ft_putchar(base[nb]);
	else
	{
		i += ft_putnbr_hexa(nb / 16, base);
		i += ft_putnbr_hexa(nb % 16, base);
	}
	return (i);
}
