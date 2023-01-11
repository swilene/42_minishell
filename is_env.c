/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:09:20 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/11 17:10:58 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

void	is_env(t_init *init, t_lexer *tmp, int i)
{
	t_env	*first;

	if (init->nb_pipe && i != init->nb_pipe)
		tmp->fd_out = init->fd_pipe[i][1];
	else if (!tmp->fd_out)
		tmp->fd_out = STDOUT_FILENO;
	first = init->env;
	while (init->env)
	{
		if (write(tmp->fd_out, init->env->str, ft_strlen(init->env->str)) < 0)
			return(perror("env"));
		if (write(tmp->fd_out, "\n", 1) < 0)
			return(perror("env"));
		init->env = init->env->next;
	}
	init->env = first;
}
