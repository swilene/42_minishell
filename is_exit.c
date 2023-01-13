/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 17:24:16 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/13 14:37:12 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

void	is_exit(t_init *init)
{
	printf("exit\n");
	free_env(init);
	free_var(init);
	if (init->path)
		free_str(init->path);
	if (init->nb_pipe)
		free_pipe(init);
	if (init->envp)
		free(init->envp);
	ft_dellist(&(init->sentence), &(init->lexer));
	rl_clear_history();
	exit(0);
}
