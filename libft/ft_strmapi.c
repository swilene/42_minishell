/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 17:39:25 by saguesse          #+#    #+#             */
/*   Updated: 2022/05/17 12:14:25 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	int		len;
	char	*str;

	len = ft_strlen(s);
	str = (char *)malloc(sizeof(*str) * len + 1);
	i = 0;
	if (!(str))
		return (NULL);
	while (s[i])
	{
		str[i] = (char)(*f)(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
