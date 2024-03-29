/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_dup_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 10:41:57 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/25 17:16:23 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

extern int	g_exit_code;

void	close_files_before_dup(t_init *init, int i, int j)
{
	t_lexer	*tmp;

	tmp = init->lexer;
	while (tmp)
	{
		if (j != i && tmp->fd_in > 0)
		{
			if (close(tmp->fd_in) < 0)
				perror(tmp->file_in);
		}
		if (j != i && tmp->fd_out > 0)
		{
			if (close(tmp->fd_out) < 0)
				perror(tmp->file_out);
		}
		tmp = tmp->next;
		j++;
	}
}

void	close_pipes_before_dup(t_init *init, int i, int j)
{
	while (j < init->nb_pipe)
	{
		if (i - 1 != j)
		{
			if (close(init->fd_pipe[j][0]) < 0)
				ft_printf("fd_pipe[%d][1]: %s\n", j, strerror(errno));
		}
		if (i != j)
		{
			if (close(init->fd_pipe[j][1]) < 0)
				ft_printf("fd_pipe[%d][1]: %s\n", j, strerror(errno));
		}
		j++;
	}
	close_files_before_dup(init, i, 0);
}

void	close_after_dup(t_init *init, t_lexer *tmp, int i)
{
	if (tmp->fd_in > 0)
	{
		if (close(tmp->fd_in) < 0)
			perror(tmp->file_in);
	}
	if (init->nb_pipe && i != 0)
	{
		if (close(init->fd_pipe[i - 1][0]) < 0)
			ft_printf("fd_pipe[%d][1]: %s\n", i, strerror(errno));
	}
	if (tmp->fd_out > 0)
	{
		if (close(tmp->fd_out) < 0)
			perror(tmp->file_out);
	}
	if (init->nb_pipe && i != init->nb_pipe)
	{
		if (close(init->fd_pipe[i][1]) < 0)
			ft_printf("fd_pipe[%d][1]: %s\n", i - 1, strerror(errno));
	}
}

void	free_before_exit(t_init *init)
{
	free_env(init);
	free_var(init);
	if (init->path)
		free_str(init->path);
	if (init->nb_pipe)
	{
		close_fd_pipe(init);
		free_pipe(init);
	}
	if (init->envp)
		free(init->envp);
	ft_dellist(&(init->sentence), &(init->lexer));
}

int	check_before_dup(t_lexer *tmp, t_init *init)
{
	if (tmp->fd_in < 0 || tmp->fd_out < 0)
	{
		g_exit_code = 1;
		if (init->nb_pipe || tmp->cmd || tmp->program)
		{
			free_before_exit(init);
			exit(g_exit_code);
		}
		return (1);
	}
	if (tmp->cmd)
		is_cmd(tmp, init);
	return (0);
}
