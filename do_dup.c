/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_dup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 17:04:59 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/11 12:24:20 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

extern int	g_exit_code;

void	dups(t_lexer *tmp, t_init *init, int i)
{
	int	err_dup_r;
	int	err_dup_w;

	err_dup_r = 0;
	err_dup_w = 0;
	if (tmp->fd_in > 0)
		err_dup_r = dup2(tmp->fd_in, STDIN_FILENO);
	else if (tmp->heredoc)
		err_dup_r = dup2(tmp->fd_heredoc[0], STDIN_FILENO);
	else if (init->nb_pipe && i != 0)
		err_dup_r = dup2(init->fd_pipe[i - 1][0], STDIN_FILENO);
	if (tmp->fd_out > 0)
		err_dup_w = dup2(tmp->fd_out, STDOUT_FILENO);
	else if (init->nb_pipe && i != init->nb_pipe)
		err_dup_w = dup2(init->fd_pipe[i][1], STDOUT_FILENO);
	close_after_dup(init, tmp, i);
	if (err_dup_r < 0 || err_dup_w < 0)
	{
		perror("dup2");
		free_before_exit(init);
		exit(g_exit_code);
	}
}

void	is_program(t_lexer *tmp, t_init *init)
{
	if (access(tmp->program, F_OK | X_OK) < 0)
	{
		perror(tmp->program);
		g_exit_code = 127;
		free_before_exit(init);
		exit(g_exit_code);
	}
	else if (tmp->program[2] == '\0')
	{
		printf("./: %s\n", strerror(EISDIR));
		g_exit_code = 126;
		free_before_exit(init);
		exit(g_exit_code);
	}
	else
		execve(tmp->program, tmp->args, init->envp);
}

void	do_dup(t_lexer *tmp, t_init *init, int i)
{
	if (check_before_dup(tmp, init))
		return ;
	if (tmp->cmd || tmp->program)
	{
		close_pipes_before_dup(init, i, 0);
		dups(tmp, init, i);
	}
	if (tmp->cmd)
	{
		execve(tmp->prog, tmp->args, init->envp);
		printf("%s: %s\n", tmp->prog, strerror(EISDIR));
		free_before_exit(init);
		exit(0);
	}
	else if (tmp->program)
		is_program(tmp, init);
	else
		execution(tmp, init, i);
}
