/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:09:20 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/20 10:50:38 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

void	is_env(t_lexer *tmp, t_init *init)
{
	t_env	*first;

	first = init->env;
	while (init->env)
	{
		if (!init->nb_pipe)
		{
			if (write(tmp->fd_out, init->env->str, ft_strlen(init->env->str)) < 0)
				return(perror("env"));
			if (write(tmp->fd_out, "\n", 1) < 0)
				return(perror("env"));
		}
		else
			printf("%s\n", init->env->str);
		init->env = init->env->next;
	}
	init->env = first;
}
