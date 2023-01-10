/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 17:21:19 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/05 10:10:14 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

extern int	g_exit_code;

void	is_cd(t_lexer *tmp)
{
	if (tmp->args[1])
	{
		if (chdir(tmp->args[1]) < 0)
		{
			g_exit_code = 1;
			perror(tmp->args[1]);
			return ;
		}
		g_exit_code = 0;
	}
	else
	{
		printf("No directory specified\n");
		g_exit_code = 1;
	}
}
