/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:30:04 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/13 16:26:18 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

void	close_fd_heredoc(t_lexer *lexer)
{
	if (close(lexer->fd_heredoc[0]) < 0)
		perror("here_doc");
	if (close(lexer->fd_heredoc[1]) < 0)
		perror("here_doc");
}

void	close_fd_pipe(t_init *init)
{
	int		i;
	t_lexer	*tmp;

	i = 0;
	while (i < init->nb_pipe)
	{
		if (close(init->fd_pipe[i][0]) < 0)
			ft_printf("fd_pipe[%d][0]: %s\n", i, strerror(errno));
		if (close(init->fd_pipe[i][1]) < 0)
			ft_printf("fd_pipe[%d][1]: %s\n", i, strerror(errno));
		i++;
	}
	tmp = init->lexer;
	while (tmp)
	{
		if (tmp->heredoc && tmp->fd_heredoc[0] > 0 && tmp->cmd)
		{
			if (close(tmp->fd_heredoc[0]) < 0)
				perror("heredoc ici");
		}
		if (tmp->heredoc && tmp->fd_heredoc[1] > 0 && tmp->cmd)
		{
			if (close(tmp->fd_heredoc[1]) < 0)
				perror("heredoc la");
		}
		else
			close_fd_heredoc(tmp);
		tmp = tmp->next;
	}
}

void	close_files(t_init *init)
{
	t_lexer	*tmp;

	tmp = init->lexer;
	while (tmp)
	{
		if (tmp->fd_in > 0 && tmp->fd_in != STDIN_FILENO)
		{
			if (close(tmp->fd_in) < 0)
				perror(tmp->file_in);
		}
		if (/*!init->nb_pipe && */tmp->fd_out > 0 && tmp->fd_out != STDOUT_FILENO
			&& tmp->fd_out != STDERR_FILENO)
		{
			if (close(tmp->fd_out) < 0)
				perror(tmp->file_out);
		}
		tmp = tmp->next;
	}
}

