/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 15:18:16 by saguesse          #+#    #+#             */
/*   Updated: 2022/05/25 15:03:20 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	length(int n)
{
	int	len;

	len = 0;
	while (n >= 1)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*write_n(int n, int len)
{
	char	*s;

	s = (char *)malloc(sizeof(*s) * (len + 1));
	if (!s)
		return (NULL);
	s[len] = '\0';
	len--;
	if (n < 0)
		n *= -1;
	while (len >= 0)
	{
		s[len] = n % 10 + '0';
		n /= 10;
		len--;
	}
	return (s);
}

char	*ft_itoa(int n)
{
	char	*s;
	int		len;

	if (n == -2147483648)
	{	
		s = ft_itoa(n + 1);
		s[10] = '8';
		return (s);
	}
	else if (n == 0)
		len = 1;
	else if (n < 0)
		len = length(n * -1) + 1;
	else
		len = length(n);
	s = write_n(n, len);
	if (n < 0)
		s[0] = '-';
	return (s);
}
