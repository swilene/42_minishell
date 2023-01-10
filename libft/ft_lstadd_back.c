/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:16:52 by saguesse          #+#    #+#             */
/*   Updated: 2022/12/06 16:21:14 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_envadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (!(*lst))
		(*lst) = new;
	else
	{
		last = ft_envlast(*lst);
		last->next = new;
	}
}

void	ft_redadd_back(t_red **lst, t_red *new)
{
	t_red	*last;

	if (!(*lst))
		(*lst) = new;
	else
	{
		last = ft_redlast(*lst);
		last->next = new;
	}
}

void	ft_lexeradd_back(t_lexer **lst, t_lexer *new)
{
	t_lexer	*last;

	if (!(*lst))
		(*lst) = new;
	else
	{
		last = ft_lexerlast(*lst);
		last->next = new;
	}
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!(*lst))
		(*lst) = new;
	else
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
}
