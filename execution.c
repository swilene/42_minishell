/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 15:45:23 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/27 17:22:27 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

extern int	g_exit_code;

void	close_pipe(t_init *init, int i)
{
	if (i != 0)
	{
		if (close(init->fd_pipe[i - 1][0] < 0))
			ft_printf("fd_pipe[%d][0]: %s\n", i - 1, strerror(errno));
	}
	if (i != init->nb_pipe)
	{
		if (close(init->fd_pipe[i][1] < 0))
			ft_printf("fd_pipe[%d][1]: %s\n", i, strerror(errno));
	}
	free_pipe(init);
	init->nb_pipe = 0;
	free_before_exit(init);
	exit(g_exit_code);
}

void	execution(t_lexer *lexer, t_init *init, int i)
{
	if (lexer->builtin)
	{
		if (ft_strcmp(lexer->builtin, "pwd") == 0)
			is_pwd(lexer, init);
		else if (ft_strcmp(lexer->builtin, "env") == 0)
			is_env(lexer, init);
		else if (ft_strcmp(lexer->builtin, "export") == 0)
			is_export(init, &(init->env), &(init->var));
		else if (ft_strcmp(lexer->builtin, "unset") == 0)
			is_unset(init, &(init->env), &(init->var));
		else if (ft_strcmp(lexer->builtin, "echo") == 0)
			is_echo(lexer, init);
		else if (ft_strcmp(lexer->builtin, "cd") == 0)
			is_cd(lexer);
		else if (ft_strcmp(lexer->builtin, "exit") == 0)
			is_exit(init, lexer);
	}
	if (init->nb_pipe)
		close_pipe(init, i);
}
