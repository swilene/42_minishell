/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:12:54 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/20 16:15:15 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	int		i1;
	int		i2;
	int		j;
	char	*str;

	i1 = ft_strlen(s1);
	i2 = ft_strlen(s2);
	j = 0;
	str = (char *)malloc(sizeof(*str) * (i1 + i2) + 1);
	if (!(str))
		return (NULL);
	while (s1[j])
	{
		str[j] = s1[j];
		j++;
	}
	j = 0;
	while (s2[j])
	{
		str[i1 + j] = s2[j];
		j++;
	}
	str[i1 + j] = '\0';
	free(s1);
	return (str);
}
