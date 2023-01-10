/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 16:42:48 by saguesse          #+#    #+#             */
/*   Updated: 2022/05/30 11:00:58 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;

	i = ft_strlen(s);
	if (c > 256)
		c %= 256;
	while (i >= 0 && s[i] != c)
		i--;
	if (i != -1)
		return ((char *)(s + i));
	else
		return (NULL);
}
