/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:06:54 by saguesse          #+#    #+#             */
/*   Updated: 2022/05/25 14:21:01 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	char			*d;
	const char		*s;

	d = dest;
	s = src;
	if (src > dest)
	{
		i = 0;
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
		return (dest);
	}
	else if (s < d)
	{
		while (n-- > 0)
			d[n] = s[n];
		return (dest);
	}
	ft_memcpy(dest, src, n);
	return (dest);
}
