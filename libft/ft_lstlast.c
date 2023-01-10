/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 10:29:05 by saguesse          #+#    #+#             */
/*   Updated: 2022/12/06 16:23:06 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_env	*ft_envlast(t_env *lst)
{
	if (lst == NULL)
		return (lst);
	else
	{
		while (lst->next != NULL)
			lst = lst->next;
	}
	return (lst);
}

t_red	*ft_redlast(t_red *lst)
{
	if (lst == NULL)
		return (lst);
	else
	{
		while (lst->next != NULL)
			lst = lst->next;
	}
	return (lst);
}

t_lexer	*ft_lexerlast(t_lexer *lst)
{
	if (lst == NULL)
		return (lst);
	else
	{
		while (lst->next != NULL)
			lst = lst->next;
	}
	return (lst);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (lst);
	else
	{
		while (lst->next != NULL)
			lst = lst->next;
	}
	return (lst);
}
