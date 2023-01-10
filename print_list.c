/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchantro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 13:59:00 by tchantro          #+#    #+#             */
/*   Updated: 2023/01/03 16:18:31 by tchantro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

void	print_list(t_env **list)
{
	t_env *first;
	int	i;
	
	if (!list)
	{
		printf("List is Empty\n");
		return ;
	}
	first = (*list);
	i = 0;
	while (*list)
	{
		printf("[%d]: %s\n", i, (*list)->str);
		(*list) = (*list)->next;
		i++;
	}
	(*list) = first;
}
