/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 15:14:54 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/07 17:03:14 by tchantro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_env *tmp, t_env **env, t_env **first)
{
	t_env	*del;

	if (*env == NULL)
		return ;
	if (ft_envsize(*env) == 1 && tmp == NULL)
	{
		printf("del_1\n");
		free((*env)->str);
		free(*env);
		(*env) = NULL;
	}
	else if (tmp == NULL)
	{
		printf("del_2\n");
		del = (*env);
		(*env) = (*env)->next;
		(*first) = (*env);
		free(del->str);
		free(del);
	}
	else if (tmp != NULL)
	{
		printf("del_3\n");
		del = (*env);
		tmp->next = (*env)->next;
		free(del->str);
		free(del);
	}
}
