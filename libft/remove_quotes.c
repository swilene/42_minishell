/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 10:35:32 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/17 16:43:36 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	single_quotes(int *i, int *len, char *word, char *str)
{
	(*i)++;
	while (word[*i] && word[*i] != '\'')
	{
		if (word[*i] != '\'')
		{
			str[*len] = word[*i];
			(*len)++;
		}
		(*i)++;
	}
}

void	double_quotes(int *i, int *len, char *word, char *str)
{
	(*i)++;
	while (word[*i] && word[*i] != '"')
	{
		if (word[*i] != '"')
		{
			str[*len] = word[*i];
			(*len)++;
		}
		(*i)++;
	}
}

char	*remove_quotes(char *word, int i, int len)
{
	char	*str;

	str = ft_calloc(1, ft_strlen(word) + 1);
	if (!str)
		return (NULL);
	while (word[i])
	{
		if (word[i] == '"')
			double_quotes(&i, &len, word, str);
		else if (word[i] == '\'')
			single_quotes(&i, &len, word, str);
		if (word[i])
		{
			if (word[i] != '"' && word[i] != '\'')
			{
				str[len] = word[i];
				len++;
			}
			i++;
		}
	}
	return (str);
}
