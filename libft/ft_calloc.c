/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 09:46:36 by saguesse          #+#    #+#             */
/*   Updated: 2022/05/25 19:20:54 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*s;

	if (nmemb == 0 || size == 0)
	{
		nmemb = 1;
		size = 1;
	}
	s = (void *)malloc(sizeof(void) * (nmemb * size));
	if (!s)
		return (NULL);
	ft_bzero(s, (nmemb * size));
	return (s);
}
