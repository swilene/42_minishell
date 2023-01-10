/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 12:41:54 by saguesse          #+#    #+#             */
/*   Updated: 2022/05/24 17:14:27 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	len = 0;
	while (dst[i] && i < size)
		i++;
	if (i == size)
		return (size + ft_strlen(src));
	j = i;
	while (size > 0 && src[len] && i < size - 1)
	{
		dst[i] = src[len];
		i++;
		len++;
	}
	if (size > 0)
		dst[i] = '\0';
	i = 0;
	while (src[i])
		i++;
	if (size < j)
		return (i + size);
	return (j + i);
}
