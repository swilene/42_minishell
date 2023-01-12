/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 15:14:54 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/12 15:51:07 by saguesse         ###   ########.fr       */
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
		free((*env)->str);
		free((*env)->quote);
		free(*env);
		(*env) = NULL;
	}
	else if (tmp == NULL)
	{
		del = (*env);
		(*env) = (*env)->next;
		(*first) = (*env);
		free(del->str);
		free(del->quote);
		free(del);
	}
	else if (tmp != NULL)
	{
		del = (*env);
		tmp->next = (*env)->next;
		free(del->str);
		free(del->quote);
		free(del);
	}
}
