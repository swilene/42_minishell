/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 09:51:29 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/25 14:31:29 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_env	*ft_envnew(char	*str)
{
	t_env	*head;

	head = malloc(sizeof(t_env));
	if (!head)
		return (NULL);
	head->str = str;
	head->next = NULL;
	return (head);
}

t_list	*ft_lstnew(char	*word)
{
	t_list	*head;

	head = malloc(sizeof(t_list));
	if (!head)
		return (free(word), NULL);
	head->word = word;
	head->var = 0;
	head->next = NULL;
	return (head);
}

t_lexer	*ft_lexernew(void)
{
	t_lexer	*head;

	head = malloc(sizeof(t_lexer));
	if (!head)
		return (NULL);
	head->cmd = NULL;
	head->prog = NULL;
	head->builtin = NULL;
	head->args = NULL;
	head->env_var = NULL;
	head->program = NULL;
	head->fd_in = 0;
	head->fd_out = 0;
	head->fd_err = 0;
	head->heredoc = NULL;
	head->red = NULL;
	head->next = NULL;
	return (head);
}

t_red	*ft_rednew(void)
{
	t_red	*head;

	head = malloc(sizeof(t_red));
	if (!head)
		return (NULL);
	head->redirection = NULL;
	head->file = NULL;
	head->fd = 0;
	head->next = NULL;
	return (head);
}
