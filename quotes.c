/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 12:48:45 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/27 14:50:36 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

int	no_quotes(t_list *tmp, int *i, char **var)
{
	int	j;

	j = *i;
	while (tmp->word[*i] && tmp->word[*i] != '"'
		&& tmp->word[*i] != '\'' && tmp->word[*i] != '$')
		(*i)++;
	(*i)--;
	if (*i - j >= 0)
	{
		*var = ft_substr(tmp->word, &j, *i - j + 1);
		if (!*var)
			return (printf("ft_substr: %s\n", strerror(ENOMEM)), 1);
	}
	return (0);
}

int	double_quotes(t_list *tmp, int *i, char **var, int j)
{
	(*i)++;
	j = *i;
	while (tmp->word[*i] && tmp->word[*i] != '"' && tmp->word[*i] != '$')
		(*i)++;
	if (*i - j >= 0)
	{
		*var = ft_substr(tmp->word, &j, *i - j);
		if (!*var)
			return (printf("ft_substr: %s\n", strerror(ENOMEM)), 1);
	}
	return (0);
}

int	quotes(t_list *tmp, int *i, char **var, int j)
{
	if (tmp->word [*i + 1] == '$' && (tmp->word[*i + 2] == '"'
			|| tmp->word[*i + 2] == '\''))
	{
		*var = ft_strdup("$");
		*i = (*i) + 2;
	}
	else if (tmp->word [*i] == '"')
	{
		if (double_quotes(tmp, i, var, 0))
			return (1);
	}
	else
	{
		(*i)++;
		j = *i;
		while (tmp->word[*i] && tmp->word[*i] != '\'')
			(*i)++;
		*var = ft_substr(tmp->word, &j, *i - j);
		if (!*var)
			return (printf("ft_substr: %s\n", strerror(ENOMEM)), 2);
	}
	return (0);
}
