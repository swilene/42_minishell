/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:12:04 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/25 14:52:04 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

int	big_str(t_list *tmp, char **str, int i)
{
	t_list	*new;
	t_list	*after;

	after = tmp->next;
	while (str[i])
	{
		new = ft_lstnew(NULL);
		if (!new)
		{
			free_str(str);
			return (printf("ft_lstnew: %s\n", strerror(ENOMEM)), 1);
		}
		new->word = ft_strdup(str[i]);
		if (!new->word)
		{
			free(new);
			free_str(str);
			return (printf("ft_strdup: %s\n", strerror(ENOMEM)), 2);
		}
		new->var = 1;
		ft_lst_add_after(&tmp, after, new);
		i++;
	}
	return (0);
}

int	not_variable(t_list *tmp)
{
	int		i;
	char	**str;

	str = ft_split_spaces(tmp->word);
	if (!str)
		return (printf("split_spaces: %s\n", strerror(ENOMEM)), 1);
	free(tmp->word);
	i = 0;
	while (str[i])
		i++;
	tmp->word = ft_strdup(str[0]);
	if (!tmp->word)
	{
		free_str(str);
		return (printf("ft_strdup: %s\n", strerror(ENOMEM)), 2);
	}
	if (i > 1)
	{
		if (big_str(tmp, str, 1))
			return (3);
	}
	free_str(str);
	return (0);
}

int	split_word(t_list *tmp)
{
	while (tmp)
	{
		if (tmp->var)
		{
			if (not_variable(tmp))
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
