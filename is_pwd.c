/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:08:53 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/27 11:05:12 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

void	is_pwd(t_lexer *tmp, t_init *init)
{
	char	pwd[4096];

	(void)tmp;
	if (getcwd(pwd, 4095) == NULL)
		perror("pwd");
	if (!init->nb_pipe && tmp->fd_out)
	{
		if (write(tmp->fd_out, pwd, ft_strlen(pwd)) < 0)
			return (perror("pwd"));
		if (write(tmp->fd_out, "\n", 1) < 0)
			return (perror("pwd"));
	}
	else
		printf("%s\n", pwd);
}
