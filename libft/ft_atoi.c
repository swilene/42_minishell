/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:41:55 by saguesse          #+#    #+#             */
/*   Updated: 2022/09/09 10:18:50 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	nb;
	int	neg;

	nb = 0;
	neg = 1;
	while (*nptr == 32 || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			neg *= -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		nb = nb * 10 + *nptr - '0';
		nptr++;
	}
	return (nb * neg);
}
