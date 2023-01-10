/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 12:34:06 by saguesse          #+#    #+#             */
/*   Updated: 2022/06/18 11:07:27 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	check_if_null(size_t nb)
{
	int	i;

	i = 0;
	if (nb == 0)
		return (i += ft_putstr("(nil)"));
	else
	{
		i += ft_putstr("0x");
		i += ft_putnbr_hexa(nb, "0123456789abcdef");
	}
	return (i);
}
