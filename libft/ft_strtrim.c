/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 16:12:39 by saguesse          #+#    #+#             */
/*   Updated: 2022/05/25 15:02:49 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*check_start(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i] && set[j])
	{
		if (s1[i] == set[j])
		{
			i++;
			j = 0;
		}
		else if (s1[i] != set[j])
			j++;
	}
	return ((char *)s1 + i);
}

static int	check_end(char const *s1, char const *set)
{
	int	len;
	int	j;

	j = 0;
	len = ft_strlen(s1) - 1;
	while (len >= 0 && set[j])
	{
		if (s1[len] == set[j])
		{
			len--;
			j = 0;
		}
		else if (s1[len] != set[j])
			j++;
	}
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		len;
	int		i;

	s1 = check_start(s1, set);
	len = check_end(s1, set);
	i = 0;
	str = (char *)malloc(sizeof(*str) * len + 2);
	if (!(str))
		return (NULL);
	while (i <= len)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return ((char *)str);
}
