/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_spaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:21:03 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/18 15:42:09 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len_word(char const *s, int i)
{
	int	len;

	len = 0;
	while (s[i] && !((s[i] >= 7 && s[i] <= 13) || s[i] == ' '))
	{
		i++;
		len++;
	}
	return (len);
}

static int	words(const char *s)
{
	int	i;
	int	nb_words;

	i = 0;
	nb_words = 0;
	while (s[i])
	{
		while (s[i] && ((s[i] >= 7 && s[i] <= 13) || s[i] == ' '))
			i++;
		if (s[i])
			nb_words++;
		while (s[i] && !((s[i] >= 7 && s[i] <= 13) || s[i] == ' '))
			i++;
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

char	**ft_split_spaces(char const *s)
{
	int		nb_words;
	int		i;
	int		j;
	int		len;
	char	**str;

	nb_words = words(s);
	i = 0;
	j = 0;
	str = malloc(sizeof(str) * (nb_words + 1));
	if (!str)
		return (NULL);
	while (j < nb_words && s[i])
	{
		while (s[i] && ((s[i] >= 7 && s[i] <= 13) || s[i] == ' '))
			i++;
		len = len_word(s, i);
		str[j] = ft_substr(s, &i, len);
		if (!str[j])
			return (clear_str(str, j), NULL);
		j++;
	}
	str[j] = NULL;
	return (str);
}
