/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saguesse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 13:59:09 by saguesse          #+#    #+#             */
/*   Updated: 2023/01/22 17:20:18 by saguesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

extern int	g_exit_code;

void	after_limiter(t_lexer *tmp, t_init *init)
{
	close_fd_heredoc(tmp);
	init->nb_pipe = 0;
	free_before_exit(init);
	exit(g_exit_code);
}

void	wait_limiter(t_lexer *tmp, char *limiter, t_init *init)
{
	char	*line;

	while (1)
	{
		signal(SIGINT, &signal_heredoc);
		line = readline("heredoc> ");
		if (!line)
		{
			if (g_exit_code != 130)
			{
				printf("warning: here-document delimited by end-of-file\n");
				g_exit_code = 130;
			}
			break ;
		}
		if (!ft_strcmp(line, limiter))
		{
			free(line);
			break ;
		}
		write(tmp->fd_heredoc[1], line, ft_strlen(line));
		write(tmp->fd_heredoc[1], "\n", 1);
		free(line);
	}
	after_limiter(tmp, init);
}

void	nothing_after_heredoc(t_lexer *tmp_lexer)
{
	if (close(tmp_lexer->fd_heredoc[0]) < 0)
		perror("heredoc[0]");
}

int	is_heredoc(t_red *tmp_red, t_lexer *tmp_lexer, t_init *init)
{
	int	pid;
	int	wstatus;

	if (!tmp_red->file)
	{
		g_exit_code = 2;
		return (printf("syntax error\n"), 1);
	}
	tmp_lexer->heredoc = "heredoc";
	if (pipe(tmp_lexer->fd_heredoc) < 0)
		return (perror("pipe"), 2);
	pid = fork();
	if (pid < 0)
		return (close_fd_heredoc(tmp_lexer), 3);
	signal(SIGINT, SIG_IGN);
	if (pid == 0)
		wait_limiter(tmp_lexer, tmp_red->file, init);
	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
		g_exit_code = WEXITSTATUS(wstatus);
	if (close(tmp_lexer->fd_heredoc[1]) < 0)
		perror("heredoc[1]");
	if (!tmp_lexer->cmd && !tmp_lexer->builtin && !tmp_lexer->program)
		nothing_after_heredoc(tmp_lexer);
	return (0);
}
