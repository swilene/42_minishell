/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:40:46 by saguesse          #+#    #+#             */
/*   Updated: 2022/12/30 12:41:16 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len_word(char const *s, char c, int i)
{
	int	len;

	len = 0;
	while (s[i] != c && s[i])
	{
		i++;
		len++;
	}
	return (len);
}

static int	words(const char *s, char c)
{
	int	i;
	int	nb_words;

	i = 0;
	nb_words = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
		{	
			while (s[i] && s[i] != c)
				i++;
			nb_words++;
		}
	}
	return (nb_words);
}

void	clear_str(char **str, int j)
{
	while (j >= 0)
	{
		free(str[j]);
		j--;
	}
	free(str);
}

char	**ft_split(char const *s, char c)
{
	int		nb_words;
	int		i;
	int		j;
	int		len;
	char	**str;

	nb_words = words(s, c);
	i = 0;
	j = 0;
	str = malloc(sizeof(str) * (nb_words + 1));
	if (!str)
		return (perror("str_split"), NULL);
	while (j < nb_words && s[i])
	{
		while (s[i] == c)
			i++;
		len = len_word(s, c, i);
		str[j] = ft_substr(s, &i, len);
		if (!str[j])
			return (clear_str(str, j), NULL);
		j++;
	}
	str[j] = NULL;
	return (str);
}
