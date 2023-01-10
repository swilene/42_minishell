/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:26:37 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/09 14:18:02 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

extern int	g_exit_code;

int	check_red(char *word)
{
	if (word[0] == '>' && word[1] == '<')
		return (printf("syntax error\n"), 1);
	else if (ft_strlen(word) == 3 && ft_strcmp(word, "<<<"))
		return (printf("syntax error\n"), 2);
	else if (ft_strlen(word) > 3)
		return (printf("syntax error\n"), 3);
	return (0);
}

char	*is_redirection(t_lexer *lexer, t_list **sentence)
{
	t_red	*new;

	if (check_red((*sentence)->word))
		return (NULL);
	new = ft_rednew();
	if (!new)
		return (NULL);
	new->redirection = ft_strdup((*sentence)->word);
	if (!new->redirection)
		return (NULL);
	if ((*sentence)->next)
	{
		new->file = ft_strdup(((*sentence)->next)->word);
		if (!new->file)
			return (NULL);
	}
	if (new->file)
		(*sentence) = (*sentence)->next;
	ft_redadd_back(&(lexer->red), new);
	return ("OK");
}
