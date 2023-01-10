/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:31:57 by saguesse          #+#    #+#             */
/*   Updated: 2022/12/08 11:45:23 by tchantro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, int *start, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *)malloc(sizeof(*str) * len + 1);
	if (!str)
		return (NULL);
	while (i < len && s[*start])
	{
		str[i] = s[*start];
		i++;
		(*start)++;
	}
	return (str[i] = '\0', str);
}
