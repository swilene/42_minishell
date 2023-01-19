/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 14:31:17 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/19 17:15:58 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

int	check_builtin(char *word)
{
	if (!ft_strcmp(word, "cd"))
		return (1);
	else if (!ft_strcmp(word, "export"))
		return (2);
	else if (!ft_strcmp(word, "unset"))
		return (3);
	else if (!ft_strcmp(word, "exit"))
		return (4);
	else if (!ft_strcmp(word, "echo"))
		return (5);
	else if (!ft_strcmp(word, "pwd"))
		return (6);
	else if (!ft_strcmp(word, "env"))
		return (7);
	return (0);
}

char	*take_args(t_list **tmp, t_lexer *new, int i, int j)
{
	t_list	*lst;

	lst = (*tmp);
	while (lst && lst->word[0] != '|' && lst->word[0] != '>' && lst->word[0]
		!= '<')
	{
		i++;
		lst = lst->next;
	}
	new->args = malloc(sizeof(new->args) * (i + 1));
	if (!new->args)
		return (NULL);
	while (j < i)
	{
		new->args[j] = ft_strdup((*tmp)->word);
		if (!new->args[j])
			return (NULL);
		free((*tmp)->word);
		(*tmp)->word = NULL;
		j++;
		if (j != i)
			(*tmp) = (*tmp)->next;
	}
	new->args[j] = NULL;
	return ("ok");
}
