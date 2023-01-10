/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dellist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 13:00:25 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/09 11:23:26 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_red(t_red **red)
{
	t_red	*tmp_red;

	if (*red)
	{
		while (*red)
		{
			tmp_red = (*red)->next;
			free((*red)->redirection);
			if ((*red)->file)
				free((*red)->file);
			free(*red);
			(*red) = tmp_red;
		}
	}
	(*red) = NULL;
}

static void	free_tmp(t_lexer *tmp)
{
	if (tmp->cmd)
		free(tmp->cmd);
	if (tmp->prog)
		free(tmp->prog);
	if (tmp->builtin)
		free(tmp->builtin);
	if (tmp->args)
		free_str(tmp->args);
	if (tmp->program)
		free(tmp->program);
}

void	ft_dellexer(t_lexer **lexer)
{
	t_lexer	*lexer_tmp;

	if (!(*lexer))
		return ;
	while (*lexer)
	{
		lexer_tmp = (*lexer)->next;
		free_red(&(*lexer)->red);
		free_tmp(*lexer);
		free_str((*lexer)->quotes);
		free(*lexer);
		(*lexer) = lexer_tmp;
	}
	(*lexer) = NULL;
}

void	ft_dellist(t_list **list, t_lexer **lexer)
{
	t_list	*tmp;

	if (*list)
	{
		while (*list)
		{
			tmp = (*list)->next;
			free((*list)->word);
			free(*list);
			(*list) = tmp;
		}
		(*list) = NULL;
	}
	ft_dellexer(lexer);
}
