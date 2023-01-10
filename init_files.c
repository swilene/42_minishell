/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:15:37 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/10 17:20:43 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

extern int	g_exit_code;

void	in_and_out_files(t_red *tmp_red, t_lexer *tmp_lexer)
{
	if (tmp_red->mode == 1 || tmp_red->mode == 2 || tmp_red->mode == 3)
	{
		if (tmp_lexer->fd_out)
		{
			if (close(tmp_lexer->fd_out) < 0)
				perror(tmp_lexer->file_out);
		}
		tmp_lexer->file_out = tmp_red->file;
		tmp_lexer->fd_out = tmp_red->fd;
	}
	else if (tmp_red->mode == 1 || tmp_red->mode == 4)
	{
		if (tmp_lexer->fd_in)
		{
			if (close(tmp_lexer->fd_in) < 0)
				perror(tmp_lexer->file_in);
		}
		tmp_lexer->file_in = tmp_red->file;
		tmp_lexer->fd_in = tmp_red->fd;
	}
}

int	open_file(t_red *tmp_red, t_lexer *tmp_lexer)
{
	if (!tmp_red->file)
	{
		g_exit_code = 2;
		tmp_red->fd = -1;
		in_and_out_files(tmp_red, tmp_lexer);
		return (printf("syntax error\n"), 1);
	}
	if (tmp_red->mode == 1)
		tmp_red->fd = open(tmp_red->file, O_RDWR | O_APPEND | O_CREAT, 00644);
	else if (tmp_red->mode == 2)
		tmp_red->fd = open(tmp_red->file, O_WRONLY | O_APPEND | O_CREAT, 00644);
	else if (tmp_red->mode == 3)
		tmp_red->fd = open(tmp_red->file, O_WRONLY | O_TRUNC | O_CREAT, 00644);
	else if (tmp_red->mode == 4)
		tmp_red->fd = open(tmp_red->file, O_RDONLY | O_APPEND);
	if (tmp_red->fd < 0)
		perror(tmp_red->file);
	in_and_out_files(tmp_red, tmp_lexer);
	return (0);
}

void	init_mode(t_red *tmp_red, t_lexer *tmp_lexer)
{
	if (!ft_strcmp(tmp_red->redirection, "<>"))
		tmp_red->mode = 1;
	else if (!ft_strcmp(tmp_red->redirection, ">>"))
		tmp_red->mode = 2;
	else if (!ft_strcmp(tmp_red->redirection, ">"))
		tmp_red->mode = 3;
	else if (!ft_strcmp(tmp_red->redirection, "<"))
		tmp_red->mode = 4;
	open_file(tmp_red, tmp_lexer);
}

char	*init_files(t_init *init)
{
	t_red	*tmp_red;
	t_lexer	*tmp_lexer;

	tmp_lexer = init->lexer;
	while (tmp_lexer)
	{
		tmp_red = tmp_lexer->red;
		while (tmp_red)
		{
			if (!ft_strcmp(tmp_red->redirection, "<<<"))
				return ("ok");
			else if (!ft_strcmp(tmp_red->redirection, "<<"))
			{
				if (is_heredoc(tmp_red, tmp_lexer, init))
					return (NULL);
			}
			else
				init_mode(tmp_red, tmp_lexer);
			tmp_red = tmp_red->next;
		}
		tmp_lexer = tmp_lexer->next;
	}
	return ("ok");
}
