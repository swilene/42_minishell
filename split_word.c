/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:12:04 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/19 16:27:50 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

void	split_word(t_list *tmp)
{
	int		i;
	char	**str;
	t_list	*new;
	t_list	*after;

	while (tmp)
	{
		i = 0;
		while (tmp->word[i])
		{
			if (tmp->word[i] == '=')
				break ;
			i++;
		}
		if (!tmp->word[i])
		{
			str = ft_split_spaces(tmp->word);


			free(tmp->word);
			i = 0;
			while (str[i])
				i++;
			tmp->word = ft_strdup(str[0]);
			if (i == 1)
				tmp = tmp->next;
			else
			{
				i = 1;
				after = tmp->next;
				while (str[i])
				{
					new = ft_lstnew(NULL);
					new->word = ft_strdup(str[i]); 
					printf("%s\n", new->word);
					printf("%p\n", after);
					printf("%s\n", tmp->word);
					ft_lst_add_after(&tmp, after, new);
					i++;
				}
			}
			free_str(str);
		}
		tmp = after;
	}
}
