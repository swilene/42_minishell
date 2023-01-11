/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:08:53 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/11 17:09:41 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

void	is_pwd(t_init *init, t_lexer *tmp, int i)
{
	char	pwd[4096];

	if (init->nb_pipe && i != init->nb_pipe)
		tmp->fd_out = init->fd_pipe[i][1];
	else if (!tmp->fd_out)
		tmp->fd_out = STDOUT_FILENO;
	if (getcwd(pwd, 4095) == NULL)
		perror("pwd");
	else
	{
		if (write(tmp->fd_out, pwd, ft_strlen(pwd)) < 0)
			return (perror("pwd"));
		if (write(tmp->fd_out, "\n", 1) < 0)
			return (perror("pwd"));
	}
}
