/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_add_after.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 11:59:04 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/19 12:27:36 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_add_after(t_list **tmp, t_list *after, t_list *new)
{
	(*tmp)->next = new;
	new->next = after;
	(*tmp) = (*tmp)->next;
}
