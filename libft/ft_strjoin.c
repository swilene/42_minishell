/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:11:09 by saguesse          #+#    #+#             */
/*   Updated: 2022/12/30 18:36:10 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
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
	return (str);
}
